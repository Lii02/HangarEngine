#include "Precompiled.h"
#include "RendererCommands.h"
#include "Direct3D11API.h"
#include <Platform/GameWindow.h>

namespace {
	RendererType g_RendererType;
	IRenderAPI* g_RendererAPI = nullptr;
}

RendererType RendererCommands::GetAPI() {
	return g_RendererType;
}

void RendererCommands::Inititialize(RendererType rendererType, GameWindow* windowPtr) {
	g_RendererType = rendererType;
	switch (rendererType)
	{
	case RendererType::DIRECTX11:
		g_RendererAPI = new Direct3D11API(windowPtr);
		break;
	}
}

void RendererCommands::DeInitialize() {
	delete g_RendererAPI;
}

void RendererCommands::BeginFrame() {
	g_RendererAPI->BeginFrame();
}

void RendererCommands::EndFrame() {
	g_RendererAPI->EndFrame();
}

uint64_t RendererCommands::CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding) {
	return g_RendererAPI->CreateDataBuffer(dataSize, dataCount, binding);
}

void RendererCommands::UpdateDataBuffer(uint64_t index, void* data) {
	g_RendererAPI->UpdateDataBuffer(index, data);
}

void RendererCommands::RemoveDataBuffer(uint64_t index) {
	g_RendererAPI->RemoveBuffer(index);
}

void RendererCommands::CleanDataBuffers() {
	g_RendererAPI->CleanDataBuffers();
}

void RendererCommands::BindVertexBuffer(uint64_t index) {
	g_RendererAPI->BindVertexBuffer(index);
}

void RendererCommands::BindIndexBuffer(uint64_t index) {
	g_RendererAPI->BindIndexBuffer(index);
}

void RendererCommands::BindConstantBuffer(uint64_t index, uint32_t slot) {
	g_RendererAPI->BindConstantBuffer(index, slot);
}

void RendererCommands::DrawIndexed(uint32_t count, uint32_t first) {
	g_RendererAPI->DrawIndexed(count, first);
}

void RendererCommands::ClearStats() {
	g_RendererAPI->ClearStats();
}

bool RendererCommands::IsVsyncEnabled() {
	return g_RendererAPI->IsVsyncEnabled();
}

void RendererCommands::SetClearColor(float clearColor[4]) {
	g_RendererAPI->SetClearColor(clearColor);
}

void RendererCommands::SetDepth(float depth) {
	g_RendererAPI->SetDepth(depth);
}

void RendererCommands::SetVsync(bool vsync) {
	g_RendererAPI->SetVsync(vsync);
}

void RendererCommands::CleanShaders() {
	g_RendererAPI->CleanShaders();
}

void RendererCommands::BindRenderShader(uint64_t index) {
	g_RendererAPI->BindRenderShader(index);
}

void RendererCommands::RemoveRenderShader(uint64_t index) {
	g_RendererAPI->RemoveRenderShader(index);
}

uint64_t RendererCommands::CreateRenderShader(const std::string_view& shaderSource, std::string vertexEntry, std::string pixelEntry, const std::vector<InputElement>& inputs) {
	return g_RendererAPI->CreateRenderShader(shaderSource, vertexEntry, pixelEntry, inputs);
}

void RendererCommands::SetTopology(RenderTopology topology) {
	g_RendererAPI->SetTopology(topology);
}

float RendererCommands::GetAspectRatio() {
	return g_RendererAPI->GetAspectRatio();
}

std::string RendererCommands::GetDeviceName() {
	return g_RendererAPI->GetDeviceName();
}

uint64_t RendererCommands::CreateTexture2D(void* data, TextureFormat format, uint32_t width, uint32_t height, uint32_t slot) {
	return g_RendererAPI->CreateTexture2D(data, format, width, height, slot);
}

void RendererCommands::BindTexture2D(uint64_t index) {
	g_RendererAPI->BindTexture2D(index);
}

void RendererCommands::RemoveTexture2D(uint64_t index) {
	g_RendererAPI->RemoveTexture2D(index);
}

void RendererCommands::CleanTextures() {
	g_RendererAPI->CleanTextures();
}

uint64_t RendererCommands::GetObjectDrawCount() {
	return g_RendererAPI->GetObjectDrawCount();
}

uint64_t RendererCommands::GetVertexDrawCount() {
	return g_RendererAPI->GetVertexDrawCount();
}