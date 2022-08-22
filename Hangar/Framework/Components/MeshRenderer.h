#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "../IComponent.h"
#include "../../Math/Vectors.h"
#include "../Material.h"

class MeshRenderer : public IComponent {
private:
	uint64_t vbo, ibo;
	MeshData3D* meshData;
	uint32_t indexCount, firstIndex;
	Material* material;
public:
	MeshRenderer(MeshData3D* meshData, uint32_t indexCount, uint32_t firstIndex = 0);
	~MeshRenderer();
	
	virtual void Initialize() override;
	virtual void Render() override;
	virtual void Update() override;
	void Unload();
	Material* GetMaterial();
	void SetMaterial(Material* newMaterial);
};

#endif