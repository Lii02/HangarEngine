#ifndef SHADERLOADER_H
#define SHADERLOADER_H
#include "../Renderer/IRenderAPI.h"

class File;

namespace ShaderLoader {
	uint64_t Load(File* file, InputElementArray inputs, std::string VS, std::string PS);
}

#endif