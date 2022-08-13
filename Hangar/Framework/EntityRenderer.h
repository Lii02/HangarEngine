#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H
#include "Entity.h"
#include "IRenderer.h"

class EntityRenderer : public IRenderer {
private:
	struct ConstantBuffer {
		Matrix projection;
		Matrix view;
		Matrix model;
	};
	ConstantBuffer cbuffer;
	float fov, nearZ, farZ;
public:
	EntityRenderer(float fov, float nearZ, float farZ);
	~EntityRenderer();
	EntityRenderer(const EntityRenderer&) = delete;

	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual void PrepareFrame() override;
	virtual void DrawEntity(Entity* e) override;
};

#endif