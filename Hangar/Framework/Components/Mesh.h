#ifndef MESH_H
#define MESH_H
#include "../IComponent.h"
#include "../../Math/Vectors.h"

class Mesh : public IComponent {
private:
	uint64_t vbo, ibo;
	MeshData3D* meshData;
	uint32_t indexCount, firstIndex;
public:
	Mesh(MeshData3D* meshData, uint32_t indexCount, uint32_t firstIndex = 0);
	~Mesh();
	
	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

#endif