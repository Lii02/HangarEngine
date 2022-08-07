#include "Precompiled.h"
#include "Direct3D11API.h"
#include "../Platform/GameWindow.h"

extern "C" {
	HANGAR_API unsigned long NvOptimusEnablement = 0x00000001;
	HANGAR_API int AmdPowerXpressRequestHighPerformance = 1;
}

using namespace DirectX;

struct Direct3D11API::IRenderAPI::VertexBuffer {
	ID3D11Buffer* buffer;
	size_t elementSize;
	size_t elementCount;
};

struct Direct3D11API::IRenderAPI::IndexBuffer {
	ID3D11Buffer* buffer;
	size_t indexCount;
};

Direct3D11API::Direct3D11API(GameWindow* windowPtr)
	: IRenderAPI(windowPtr) {
	Initialize();
}

Direct3D11API::~Direct3D11API() {
	DeInitialize();
}

void Direct3D11API::Initialize() {
	CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
	uint32_t i;

	IDXGIAdapter1* currentAdapter;
	for (i = 0; factory->EnumAdapters1(i, &currentAdapter) != DXGI_ERROR_NOT_FOUND; i++) {
		DXGI_ADAPTER_DESC1 desc;
		currentAdapter->GetDesc1(&desc);
		adapters.push_back({ i, desc, currentAdapter });
	}

	// TODO: Select adapter
	GPU& selectedGPU = adapters[0];

	IDXGIOutput* currentOutput;
	for (i = 0; selectedGPU.adapter->EnumOutputs(i, &currentOutput) != DXGI_ERROR_NOT_FOUND; i++) {
		uint32_t modeCount = 0;
		currentOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modeCount, NULL);
		DXGI_MODE_DESC* modes = new DXGI_MODE_DESC[modeCount];
		currentOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modeCount, modes);
		Monitor m = { i, currentOutput, modes, modeCount };
		monitors.push_back(m);
	}
	uint32_t createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	uint32_t numFeatureLevels = ARRAYSIZE(featureLevels);
	HRESULT result;

	result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext);

	uint32_t width = windowPtr->GetWidth();
	uint32_t height = windowPtr->GetHeight();
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = (HWND)windowPtr->GetHandle();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	result = factory->CreateSwapChain(device, &sd, &swapchain);

	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer, nullptr, &renderTargetView);
	pBackBuffer->Release();

	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, width, height, 1, 1, D3D11_BIND_DEPTH_STENCIL);
	ID3D11Texture2D* depthStencilTexture;
	device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilTexture);
	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	device->CreateDepthStencilView(depthStencilTexture, &depthStencilViewDesc, &depthStencilView);
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	SetViewport();
	depthStencilTexture->Release();
	commonStates = new CommonStates(device);
	rasterState = commonStates->CullCounterClockwise();
	blendState = commonStates->Opaque();
}

void Direct3D11API::DeInitialize() {
	for (Monitor& m : monitors) {
		delete[] m.modes;
	}

	delete commonStates;
	CleanVertexBuffers();
	CleanIndexBuffers();
	depthStencilView->Release();
	renderTargetView->Release();
	swapchain->Release();
	deviceContext->Release();
	device->Release();
	factory->Release();
}

void Direct3D11API::BeginFrame() {
	deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, 0);
	deviceContext->RSSetState(rasterState);
	deviceContext->OMSetBlendState(blendState, NULL, 0xFFFFFFFF);
	ClearStats();
}

void Direct3D11API::EndFrame() {
	swapchain->Present(vsync, 0);
}

uint64_t Direct3D11API::CreateVertexBuffer(size_t vertexSize, size_t vertexCount) {
	VertexBuffer* vbo = new VertexBuffer;
	vbo->elementCount = vertexCount;
	vbo->elementSize = vertexCount;
	D3D11_BUFFER_DESC desc = { };
	desc.ByteWidth = vertexCount * vertexSize;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, nullptr, &vbo->buffer);
	vertexBuffers.push_back(vbo);
	return vertexBuffers.size() - 1;
}

void Direct3D11API::UpdateVertexBuffer(uint64_t index, void* data) {
	auto& vbo = vertexBuffers[index];
	D3D11_MAPPED_SUBRESOURCE subresource;
	deviceContext->Map(vbo->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
	memcpy(subresource.pData, data, vbo->elementSize * vbo->elementCount);
	deviceContext->Unmap(vbo->buffer, 0);
}

void Direct3D11API::CleanVertexBuffers() {
	for (auto& vbo : vertexBuffers) {
		vbo->buffer->Release();
		delete vbo;
	}
	vertexBuffers.clear();
}

void Direct3D11API::CleanIndexBuffers() {
	for (auto& ibo : indexBuffers) {
		ibo->buffer->Release();
		delete ibo;
	}
	indexBuffers.clear();
}

uint64_t Direct3D11API::CreateIndexBuffer(size_t indexSize, size_t indexCount) {
	IndexBuffer* ibo = new IndexBuffer;
	ibo->indexCount = indexCount;
	D3D11_BUFFER_DESC desc = { };
	desc.ByteWidth = sizeof(int) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, nullptr, &ibo->buffer);
	indexBuffers.push_back(ibo);
	return indexBuffers.size() - 1;
}

void Direct3D11API::UpdateIndexBuffer(uint64_t index, void* data) {
	auto& ibo = indexBuffers[index];
	D3D11_MAPPED_SUBRESOURCE subresource;
	deviceContext->Map(ibo->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
	memcpy(subresource.pData, data, sizeof(int) * ibo->indexCount);
	deviceContext->Unmap(ibo->buffer, 0);
}

void Direct3D11API::BindVertexBuffer(uint64_t index) {
	UINT stride = vertexBuffers[index]->elementSize;
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffers[index]->buffer, &stride, &offset);
}

void Direct3D11API::BindIndexBuffer(uint64_t index) {
	deviceContext->IASetIndexBuffer(indexBuffers[index]->buffer, DXGI_FORMAT_R32_UINT, 0);
}

void Direct3D11API::DrawIndexed(uint32_t count, uint32_t first) {
	objectDrawCount++;
	vertexDrawCount += count;
	deviceContext->DrawIndexed(count, first, 0);
}

void Direct3D11API::SetViewport() {
	D3D11_VIEWPORT vp;
	vp.Width = (float)windowPtr->GetWidth();
	vp.Height = (float)windowPtr->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = depth;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &vp);
}