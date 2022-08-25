#include "Precompiled.h"
#include "ShaderLoader.h"
#include <IO/File.h>
#include <Debug/Logger.h>
#include <Renderer/RendererCommands.h>

uint64_t ShaderLoader::Load(File* file, InputElementArray inputs, std::string VS, std::string PS) {
	uint64_t shader = 0;
	if (!file->ReOpen()) {
		Logger::Error("Failed to load shader file: " + file->GetPath());
		delete file;
		return shader;
	}
	shader = RendererCommands::CreateRenderShader(file->ReadString(file->Length()), VS, PS, inputs);

	file->Rewind();
	Logger::Confirmation("Loaded " + file->GetFilename() + " shader file");
	return shader;
}