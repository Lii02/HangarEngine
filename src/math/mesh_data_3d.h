#ifndef MESHDATA_H
#define MESHDATA_H

typedef std::vector<int> Indices;
typedef std::vector<StandardVertex3D> StandardVertices3D;

struct MeshData3D {
	std::string name;
	StandardVertices3D vertices;
	Indices indices;

	MeshData3D() = default;
	MeshData3D(std::string name, StandardVertices3D vertices, Indices indices) {
		this->name = name;
		this->vertices = vertices;
		this->indices = indices;
	}
};

#endif