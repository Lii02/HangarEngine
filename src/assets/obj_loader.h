#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "../Math/Vectors.h"

class File;
class Material;

typedef std::pair<MeshData3D, Material*> ObjMeshData;

namespace OBJLoader {
	std::vector<ObjMeshData> Load(File* file);
}

#endif