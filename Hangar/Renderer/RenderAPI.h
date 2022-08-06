#ifndef RENDER_API_H
#define RENDER_API_H

class GameWindow;

class IRenderAPI {
protected:
	GameWindow* windowPtr;
	uint64_t objectDrawCount; // # of objects being draw
	uint64_t vertexDrawCount; // # of vertices being draw
public:
	IRenderAPI(GameWindow* windowPtr) : windowPtr(windowPtr), objectDrawCount(0), vertexDrawCount(0) { }
	IRenderAPI(const IRenderAPI&) = delete;
	virtual ~IRenderAPI() { }

	virtual void Initialize() = 0;
	virtual void DeInitialize() = 0;

	inline uint64_t GetObjectDrawCount() const { return objectDrawCount; };
	inline uint64_t GetVertexDrawCount() const { return vertexDrawCount; };
};

#endif