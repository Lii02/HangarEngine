#ifndef RENDERER_COMMANDS_H
#define RENDERER_COMMANDS_H
#include "IRenderAPI.h"

enum class RendererType {
	DIRECTX11,
};

class GameWindow;

class RendererCommands {
public:
	static IRenderAPI* api;

	static RendererType GetAPI();
	static void Init(RendererType rendererType, GameWindow* windowPtr);
	static void DeInitialize();
	static void BeginFrame();
	static void EndFrame();
	static uint64_t CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding);
	static void UpdateDataBuffer(uint64_t index, void* data);
	static void RemoveDataBuffer(uint64_t index);
	static void CleanDataBuffers();
	static void BindVertexBuffer(uint64_t index);
	static void BindIndexBuffer(uint64_t index);
	static void BindConstantBuffer(uint64_t index, uint32_t slot);
	static void DrawIndexed(uint32_t count, uint32_t first = 0);
	static void ClearStats();
	static bool IsVsyncEnabled();
	static void SetClearColor(float clearColor[4]);
	static void SetDepth(float depth);
	static void SetVsync(bool vsync);
	static void CleanShaders();
	static void BindRenderShader(uint64_t index);
	static void RemoveRenderShader(uint64_t index);
	static uint64_t CreateRenderShader(const std::string_view& shaderSource, std::string vertexEntry, std::string pixelEntry, const std::vector<InputElement>& inputs);
	static void SetTopology(RenderTopology topology);
	static float GetAspectRatio();
	static std::string GetDeviceName();
	static uint64_t CreateTexture2D(void* data, TextureFormat format, uint32_t width, uint32_t height, uint32_t slot);
	static void BindTexture2D(uint64_t index);
	static void RemoveTexture2D(uint64_t index);
	static void CleanTextures();

	static uint64_t GetObjectDrawCount();
	static uint64_t GetVertexDrawCount();
};

#endif