#ifndef RENDERER_COMMANDS_H
#define RENDERER_COMMANDS_H

enum class RendererType {
	DIRECTX11,
};

class IRenderAPI;
class GameWindow;
enum DataBufferBinding;

class RendererCommands {
public:
	static IRenderAPI* api;

	static void Init(RendererType rendererType, GameWindow* windowPtr);
	static void DeInitialize();
	static void BeginFrame();
	static void EndFrame();
	static uint64_t CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding);
	static void UpdateDataBuffer(uint64_t index, void* data);
	static void CleanDataBuffers();
	static void BindVertexBuffer(uint64_t index);
	static void BindIndexBuffer(uint64_t index);
	static void DrawIndexed(uint32_t count, uint32_t first = 0);
	static void ClearStats();
	static bool IsVsyncEnabled();
	static void SetClearColor(float clearColor[4]);
	static void SetDepth(float depth);
	static void SetVsync(bool vsync);
};

#endif