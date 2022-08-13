#include "Precompiled.h"
#include "RendererCommands.h"
#include "Direct3D11API.h"
#include "../Platform/GameWindow.h"

IRenderAPI* RendererCommands::api = nullptr;

void RendererCommands::Init(RendererType rendererType, GameWindow* windowPtr) {
	switch (rendererType)
	{
	case RendererType::DIRECTX11:
		api = new Direct3D11API(windowPtr); 
		break;
	}
}

void RendererCommands::DeInitialize() {
	delete api;
}

void RendererCommands::BeginFrame() {
	api->BeginFrame();
}

void RendererCommands::EndFrame() {
	api->EndFrame();
}

uint64_t RendererCommands::CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding) {
	return api->CreateDataBuffer(dataSize, dataCount, binding);
}

void RendererCommands::UpdateDataBuffer(uint64_t index, void* data) {
	api->UpdateDataBuffer(index, data);
}

void RendererCommands::RemoveDataBuffer(uint64_t index) {
	api->RemoveBuffer(index);
}

void RendererCommands::CleanDataBuffers() {
	api->CleanDataBuffers();
}

void RendererCommands::BindVertexBuffer(uint64_t index) {
	api->BindVertexBuffer(index);
}

void RendererCommands::BindIndexBuffer(uint64_t index) {
	api->BindIndexBuffer(index);
}

void RendererCommands::DrawIndexed(uint32_t count, uint32_t first) {
	api->DrawIndexed(count, first);
}

void RendererCommands::ClearStats() {
	api->ClearStats();
}

bool RendererCommands::IsVsyncEnabled() {
	return api->IsVsyncEnabled();
}

void RendererCommands::SetClearColor(float clearColor[4]) {
	api->SetClearColor(clearColor);
}

void RendererCommands::SetDepth(float depth) {
	api->SetDepth(depth);
}

void RendererCommands::SetVsync(bool vsync) {
	api->SetVsync(vsync);
}

void RendererCommands::CleanShaders() {
	api->CleanShaders();
}

void RendererCommands::BindRenderShader(uint64_t index) {
	api->BindRenderShader(index);
}

uint64_t RendererCommands::CreateRenderShader(const std::string_view& shaderSource, std::string vertexEntry, std::string pixelEntry, const std::vector<InputElement>& inputs) {
	return api->CreateRenderShader(shaderSource, vertexEntry, pixelEntry, inputs);
}

uint64_t RendererCommands::GetObjectDrawCount() {
	return api->GetObjectDrawCount();
}

uint64_t RendererCommands::GetVertexDrawCount() {
	return api->GetVertexDrawCount();
}