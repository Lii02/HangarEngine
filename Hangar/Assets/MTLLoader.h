#ifndef MATLOADER_H
#define MATLOADER_H
#include "Material.h"

class File;

namespace MTLLoader {
	std::unordered_map<std::string, Material*> Load(File* file);
}

#endif