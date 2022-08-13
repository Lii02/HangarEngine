#ifndef MESHDATA_H
#define MESHDATA_H

typedef std::vector<int> Indices;
typedef std::vector<StandardVertex3D> StandardVertices3D;

struct MeshData3D {
	StandardVertices3D vertices;
	Indices indices;

	MeshData3D() = default;
	MeshData3D(StandardVertices3D vertices, Indices indices) {
		this->vertices = vertices;
		this->indices = indices;
	}
	MeshData3D(const MeshData3D&) = delete;
};

#endif