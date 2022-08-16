#include "Precompiled.h"
#include "TextureManager.h"

namespace {
	TextureManager g_TextureManager;
}

TextureManager& TextureManager::Get() {
	return g_TextureManager;
}

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
	CleanTextures();
}

void TextureManager::AddTexture(std::string name, Texture2D* texture) {
	textures.emplace(std::make_pair(name, texture));
}

void TextureManager::CleanTextures() {
	for (auto& [name, texture] : textures) {
		delete texture;
	}
	textures.clear();
}

const Texture2D* TextureManager::GetTexture(std::string name) {
	return textures[name];
}

void TextureManager::RemoveTexture(std::string name) {
	delete textures[name];;
	textures.erase(name);
}