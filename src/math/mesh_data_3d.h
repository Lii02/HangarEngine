#ifndef MESHDATA_H
#define MESHDATA_H
#include "containers/list.h"

typedef List<int> Indices;
typedef List<StandardVertex3D> StandardVertices3D;

struct MeshData3D {
	std::string name;
	StandardVertices3D vertices;
	Indices indices;

	MeshData3D() = default;
	MeshData3D(std::string _name, StandardVertices3D _vertices, Indices _indices) {
		name = _name;
		vertices = _vertices;
		indices = _indices;
	}
};

#endif