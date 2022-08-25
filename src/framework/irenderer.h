#ifndef IRENDERER_H
#define IRENDERER_H

class Entity;

class IRenderer {
protected:
	uint64_t shader;
	uint64_t constantBuffer;
	Matrix projectionMatrix;
public:
	virtual ~IRenderer() { };

	virtual void Initialize() = 0;
	virtual void DeInitialize() = 0;
	virtual void PrepareFrame(Entity* camera, Matrix projection) = 0;
	virtual void DrawEntity(Entity* e) = 0;
};

#endif