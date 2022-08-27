#ifndef MESHDATA_H
#define MESHDATA_H
#include "containers/list.h"
#include "math/vectors.h"
#include "string/astring.h"

typedef List<int> Indices;
typedef List<StandardVertex3D> StandardVertices3D;

struct MeshData3D {
	AString name;
	StandardVertices3D vertices;
	Indices indices;

	MeshData3D() = default;
	MeshData3D(AString _name, StandardVertices3D _vertices, Indices _indices) {
		name = _name;
		vertices = _vertices;
		indices = _indices;
	}
};

#endif