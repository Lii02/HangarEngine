#ifndef RENDER_API_H
#define RENDER_API_H

class GameWindow;

class IRenderAPI {
protected:
	GameWindow* windowPtr;
	uint64_t objectDrawCount; // # of objects being draw
	uint64_t vertexDrawCount; // # of vertices being draw
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float depth;
	bool vsync;
	struct VertexBuffer;
	std::vector<VertexBuffer*> vertexBuffers;
	struct IndexBuffer;
	std::vector<IndexBuffer*> indexBuffers;
public:
	IRenderAPI(GameWindow* windowPtr) : windowPtr(windowPtr), objectDrawCount(0), vertexDrawCount(0), depth(1.0f), vsync(true) { }
	IRenderAPI(const IRenderAPI&) = delete;
	virtual ~IRenderAPI() { }

	virtual void Initialize() = 0;
	virtual void DeInitialize() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual uint64_t CreateVertexBuffer(size_t vertexSize, size_t vertexCount) = 0;
	virtual void UpdateVertexBuffer(uint64_t index, void* data) = 0;
	virtual uint64_t CreateIndexBuffer(size_t indexSize, size_t indexCount) = 0;
	virtual void UpdateIndexBuffer(uint64_t index, void* data) = 0;
	virtual void CleanVertexBuffers() = 0;
	virtual void CleanIndexBuffers() = 0;
	virtual void BindVertexBuffer(uint64_t index) = 0;
	virtual void BindIndexBuffer(uint64_t index) = 0;
	virtual void DrawIndexed(uint32_t count, uint32_t first = 0) = 0;

	inline void ClearStats() {
		this->objectDrawCount = 0;
		this->vertexDrawCount = 0;
	}
	inline bool IsVsyncEnabled() const { return vsync; }
	inline void SetClearColor(float clearColor[4]) { memcpy(this->clearColor, clearColor, sizeof(float) * 4); }
	inline void SetDepth(float depth) { this->depth = depth; }
	inline void SetVsync(bool vsync) { this->vsync = vsync; }
	inline uint64_t GetObjectDrawCount() const { return objectDrawCount; };
	inline uint64_t GetVertexDrawCount() const { return vertexDrawCount; };
};

#endif