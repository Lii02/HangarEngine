#include "Precompiled.h"
#include "Texture2D.h"
#include "../Renderer/RendererCommands.h"

Texture2D::Texture2D(uint32_t width, uint32_t height, uint32_t slot, TextureFormat format) {
	this->width = width;
	this->height = height;
	this->slot = slot;
	this->format = format;
}

Texture2D::~Texture2D() {
	DeInitialize();
}

void Texture2D::Initialize(void* data) {
	this->index = RendererCommands::CreateTexture2D(data, format, width, height, slot);
}

void Texture2D::DeInitialize() {
	RendererCommands::RemoveTexture2D(index);
}

void Texture2D::Bind() {
	RendererCommands::BindTexture2D(index);
}