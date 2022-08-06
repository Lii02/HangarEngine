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
	struct VertexBuffer;
	std::vector<VertexBuffer*> vertexBuffers;
public:
	IRenderAPI(GameWindow* windowPtr) : windowPtr(windowPtr), objectDrawCount(0), vertexDrawCount(0), depth(1.0f) { }
	IRenderAPI(const IRenderAPI&) = delete;
	virtual ~IRenderAPI() { }

	virtual void Initialize() = 0;
	virtual void DeInitialize() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual uint64_t CreateVertexBuffer(size_t vertexSize, size_t vertexCount, void* data) = 0;
	
	inline void ClearStats() {
		this->objectDrawCount = 0;
		this->vertexDrawCount = 0;
	}
	inline void SetClearColor(float clearColor[4]) { memcpy(this->clearColor, clearColor, sizeof(float) * 4); }
	inline void SetDepth(float depth) { this->depth = depth; }
	inline uint64_t GetObjectDrawCount() const { return objectDrawCount; };
	inline uint64_t GetVertexDrawCount() const { return vertexDrawCount; };
};

#endif