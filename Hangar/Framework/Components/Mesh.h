#ifndef MESH_H
#define MESH_H
#include "../IComponent.h"
#include "../../Math/Vectors.h"

class Mesh : public IComponent {
public:
	typedef std::vector<int> Indices;
	typedef std::vector<StandardVertex3D> Vertices;
private:
	uint64_t vbo, ibo;
	Indices* indices;
	Vertices* vertices;
	uint32_t indexCount;
public:
	Mesh(Vertices* vertices, Indices* indices, uint32_t indexCount);
	~Mesh();
	
	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

#endif