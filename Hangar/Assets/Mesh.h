#ifndef MESH_H
#define MESH_H

struct MeshData3D;
class Material;

class Mesh {
private:
	uint64_t vbo, ibo;
	MeshData3D* meshData;
	uint32_t indexCount, firstIndex;
	Material* material;
public:
	Mesh(MeshData3D* meshData, uint32_t indexCount, uint32_t firstIndex = 0);
	~Mesh();

	void Initialize();
	void Render();
	void Unload();
	Material* GetMaterial();
	void SetMaterial(Material* newMaterial);
};

#endif