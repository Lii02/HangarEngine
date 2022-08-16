#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H
#include "Entity.h"
#include "IRenderer.h"

class EntityRenderer : public IRenderer {
private:
	struct alignas(16) ConstantBuffer {
		Matrix projection;
		Matrix view;
		Matrix model;
	};
	ConstantBuffer cbuffer;
public:
	EntityRenderer();
	~EntityRenderer();
	EntityRenderer(const EntityRenderer&) = delete;

	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual void PrepareFrame(Entity* camera, Matrix projection) override;
	virtual void DrawEntity(Entity* e) override;
};

#endif