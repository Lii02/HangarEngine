#include "Precompiled.h"
#include "Direct3D11API.h"
#include "../Platform/GameWindow.h"
#include "../Debug/Logger.h"
#include "../Memory/MemoryManager.h"
#include <d3dcompiler.h>

extern "C" {
	HANGAR_API unsigned long NvOptimusEnablement = 0x00000001;
	HANGAR_API int AmdPowerXpressRequestHighPerformance = 1;
}

using namespace DirectX;

struct Direct3D11API::IRenderAPI::DataBuffer {
	ID3D11Buffer* buffer;
	size_t elementSize;
	size_t elementCount;

	~DataBuffer() {
		buffer->Release();
	}
};

struct Direct3D11API::IRenderAPI::RenderShader {
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	std::string vertexEntry, pixelEntry;

	~RenderShader() {
		vertexShader->Release();
		pixelShader->Release();
		layout->Release();
	}
};

struct Direct3D11API::IRenderAPI::Texture2D {
	uint32_t slot, components, width, height;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* resource;

	~Texture2D() {
		texture->Release();
		resource->Release();
	}
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
	this->selectedGPU = &adapters[0];

	IDXGIOutput* currentOutput;
	for (i = 0; selectedGPU->adapter->EnumOutputs(i, &currentOutput) != DXGI_ERROR_NOT_FOUND; i++) {
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

	ID3D11Texture2D* backBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
	backBuffer->Release();

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
	CleanTextures();
	CleanShaders();
	CleanDataBuffers();
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

uint64_t Direct3D11API::CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding) {
	DataBuffer* buffer = new DataBuffer;
	buffer->elementCount = dataCount;
	buffer->elementSize = dataSize;
	D3D11_BUFFER_DESC desc = { };
	size_t bufferSize = dataSize * dataCount;
	desc.ByteWidth = bufferSize;
	switch (binding) {
	case DataBufferBinding::VERTEX_BUFFER:
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
	case DataBufferBinding::INDEX_BUFFER:
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
	case DataBufferBinding::CONSTANT_BUFFER:
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, nullptr, &buffer->buffer);
	dataBuffers.push_back(buffer);
	return dataBuffers.size() - 1;
}

void Direct3D11API::UpdateDataBuffer(uint64_t index, void* data) {
	auto& vbo = dataBuffers[index];
	D3D11_MAPPED_SUBRESOURCE subresource;
	deviceContext->Map(vbo->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
	memcpy(subresource.pData, data, vbo->elementSize * vbo->elementCount);
	deviceContext->Unmap(vbo->buffer, 0);
}

void Direct3D11API::CleanDataBuffers() {
	for (auto& vbo : dataBuffers) {
		if(vbo)
			delete vbo;
	}
	dataBuffers.clear();
}

void Direct3D11API::BindVertexBuffer(uint64_t index) {
	uint32_t stride = dataBuffers[index]->elementSize;
	uint32_t offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &dataBuffers[index]->buffer, &stride, &offset);
}

void Direct3D11API::BindIndexBuffer(uint64_t index) {
	deviceContext->IASetIndexBuffer(dataBuffers[index]->buffer, DXGI_FORMAT_R32_UINT, 0);
}

void Direct3D11API::DrawIndexed(uint32_t count, uint32_t first) {
	objectDrawCount++;
	vertexDrawCount += count;
	deviceContext->DrawIndexed(count, first, 0);
}

void Direct3D11API::CleanShaders() {
	for (auto& shader : renderShaders) {
		delete shader;
	}
	renderShaders.clear();
}

void Direct3D11API::BindRenderShader(uint64_t index) {
	auto& shader = renderShaders[index];
	deviceContext->IASetInputLayout(shader->layout);
	deviceContext->VSSetShader(shader->vertexShader, 0, 0);
	deviceContext->PSSetShader(shader->pixelShader, 0, 0);
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

uint64_t Direct3D11API::CreateTexture2D(void* data, TextureFormat format, uint32_t width, uint32_t height, uint32_t slot) {
	Texture2D* texture = new Texture2D;
	texture->slot = slot;
	texture->width = width;
	texture->height = height;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 0;
	desc.ArraySize = 1;
	switch (format)
	{
	case TextureFormat::R8G8B8A8:
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture->components = 4;
		break;
	}
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	device->CreateTexture2D(&desc, nullptr, &texture->texture);
	deviceContext->UpdateSubresource(texture->texture, 0, nullptr, data, width * texture->components, 0);
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc = {};
	resDesc.Format = desc.Format;
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Texture2D.MostDetailedMip = 0;
	resDesc.Texture2D.MipLevels = -1;
	device->CreateShaderResourceView(texture->texture, &resDesc, &texture->resource);
	deviceContext->GenerateMips(texture->resource);
	textures.push_back(texture);
	return textures.size() - 1;
}

void Direct3D11API::BindTexture2D(uint64_t index) {
	auto& texture = textures[index];
	deviceContext->PSSetShaderResources(texture->slot, 1, &texture->resource);
}

void Direct3D11API::RemoveTexture2D(uint64_t index) {
	auto& texture = textures[index];
	delete texture;
	texture = nullptr;
}

void Direct3D11API::CleanTextures() {
	for (auto& texture : textures) {
		delete texture;
	}
	textures.clear();
}

std::string Direct3D11API::GetDeviceName() {
	std::wstring str = selectedGPU->info.Description;
	return std::string(str.begin(), str.end());
}

void Direct3D11API::BindConstantBuffer(uint64_t index) {
	auto& buffer = dataBuffers[index];
	deviceContext->VSSetConstantBuffers(0, 1, &buffer->buffer);
	deviceContext->PSSetConstantBuffers(0, 1, &buffer->buffer);
}

float Direct3D11API::GetAspectRatio() {
	return (float)windowPtr->GetWidth() / (float)windowPtr->GetHeight();
}

void Direct3D11API::RemoveRenderShader(uint64_t index) {
	auto& shader = renderShaders[index];
	delete shader;
	shader = nullptr;
}

void Direct3D11API::SetTopology(RenderTopology topology) {
	switch (topology) {
	case RenderTopology::LINES:
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case RenderTopology::TRIANGLES:
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case RenderTopology::POINTS:
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	}
}

void Direct3D11API::RemoveBuffer(uint64_t index) {
	auto& buffer = dataBuffers[index];
	delete buffer;
	buffer = nullptr;
}

uint64_t Direct3D11API::CreateRenderShader(std::string_view shaderSource, std::string vertexEntry, std::string pixelEntry, std::vector<InputElement> inputs) {
	RenderShader* shader = new RenderShader;
	ID3DBlob* vsBlob = nullptr, *psBlob = nullptr, *errorBlob = nullptr;
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined(_DEBUG)
	flags |= D3DCOMPILE_DEBUG;
#endif
	D3DCompile(shaderSource.data(), shaderSource.length(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, vertexEntry.c_str(), "vs_5_0", flags, 0, &vsBlob, &errorBlob);
	D3DCompile(shaderSource.data(), shaderSource.length(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pixelEntry.c_str(), "ps_5_0", flags, 0, &psBlob, &errorBlob);
	if (errorBlob) {
		std::string errorString = (char*)errorBlob->GetBufferPointer();
		Logger::Error(errorString);
	}

	device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &shader->vertexShader);
	device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &shader->pixelShader);

	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	for (size_t i = 0; i < inputs.size(); i++) {
		D3D11_INPUT_ELEMENT_DESC desc;
		InputElement element = inputs[i];
		desc.SemanticName = new char[16] { 0 };
		strcpy((char*)desc.SemanticName, element.name.c_str());
		desc.SemanticIndex = 0;
		switch (element.numFloats) {
		case 1:
			desc.Format = DXGI_FORMAT_R32_FLOAT;
			break;
		case 2:
			desc.Format = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case 3:
			desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case 4:
			desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		}
		desc.InputSlot = 0;
		if(i > 0)
			desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		else
			desc.AlignedByteOffset = 0;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		descs.push_back(desc);
	}
	
	device->CreateInputLayout(descs.data(), inputs.size(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &shader->layout);

	for (size_t i = 0; i < inputs.size(); i++) {
		D3D11_INPUT_ELEMENT_DESC& desc = descs[i];
		delete[] desc.SemanticName;
	}

	renderShaders.push_back(shader);
	return renderShaders.size() - 1;
}