#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "../Math/Vectors.h"

class File;

namespace OBJLoader {
	std::vector<MeshData3D> Load(File* file);
}

#endif