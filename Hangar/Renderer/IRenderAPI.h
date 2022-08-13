#ifndef RENDER_API_H
#define RENDER_API_H

class GameWindow;

enum DataBufferBinding : uint8_t {
	VERTEX_BUFFER,
	INDEX_BUFFER,
	CONSTANT_BUFFER
};

enum class Topology {
	LINE,
	TRIANGLES,
	POINTS,
};

struct InputElement {
	int index, numFloats, offset;
	std::string name;
};

typedef std::vector<InputElement> InputElementArray;

class IRenderAPI {
protected:
	GameWindow* windowPtr;
	uint64_t objectDrawCount; // # of objects being draw
	uint64_t vertexDrawCount; // # of vertices being draw
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float depth;
	bool vsync;
	struct DataBuffer;
	std::vector<DataBuffer*> dataBuffers;
	struct RenderShader;
	std::vector<RenderShader*> renderShaders;
public:
	IRenderAPI(GameWindow* windowPtr) : windowPtr(windowPtr), objectDrawCount(0), vertexDrawCount(0), depth(1.0f), vsync(true) { }
	virtual ~IRenderAPI() { }
	IRenderAPI(const IRenderAPI&) = delete;

	virtual void Initialize() = 0;
	virtual void DeInitialize() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual uint64_t CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding) = 0;
	virtual void UpdateDataBuffer(uint64_t index, void* data) = 0;
	virtual void RemoveBuffer(uint64_t index) = 0;
	virtual void CleanDataBuffers() = 0;
	virtual void BindVertexBuffer(uint64_t index) = 0;
	virtual void BindIndexBuffer(uint64_t index) = 0;
	virtual void DrawIndexed(uint32_t count, uint32_t first = 0) = 0;
	virtual void CleanShaders() = 0;
	virtual void BindRenderShader(uint64_t index) = 0;
	virtual uint64_t CreateRenderShader(std::string_view shaderSource, std::string vertexEntry, std::string pixelEntry, std::vector<InputElement> inputs) = 0;
	virtual void SetTopology(Topology topology) = 0;

	void ClearStats();
	inline bool IsVsyncEnabled() const { return vsync; }
	inline void SetClearColor(float clearColor[4]) { memcpy(this->clearColor, clearColor, sizeof(float) * 4); }
	inline void SetDepth(float depth) { this->depth = depth; }
	inline void SetVsync(bool vsync) { this->vsync = vsync; }
	inline uint64_t GetObjectDrawCount() const { return objectDrawCount; };
	inline uint64_t GetVertexDrawCount() const { return vertexDrawCount; };
};

#endif