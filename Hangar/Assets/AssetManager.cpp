#include "Precompiled.h"
#include "AssetManager.h"
#include "Texture2D.h"
#include "AudioClip.h"
#include "Material.h"

namespace {
	AssetManager* g_AssetManager;
}

AssetManager*& AssetManager::Get() {
	return g_AssetManager;
}

void AssetManager::Initialize() {
	g_AssetManager = new AssetManager();
}

void AssetManager::DeInitialize() {
	delete g_AssetManager;
}

AssetManager::AssetManager() {
}

AssetManager::~AssetManager() {
	for (auto& [name, texture] : textures)
		delete texture;
	textures.clear();

	for (auto& [name, clip] : sounds)
		delete clip;
	sounds.clear();

	for (auto& [name, material] : materials)
		delete material;
	materials.clear();
}

void AssetManager::AddTexture(std::string name, Texture2D* texture) {
	textures.emplace(std::make_pair(name, texture));
}

void AssetManager::AddSound(std::string name, AudioClip* sound) {
	sounds.emplace(std::make_pair(name, sound));
}

void AssetManager::AddMaterials(std::string name, Material* material) {
	materials.emplace(std::make_pair(name, material));
}

Texture2D* AssetManager::GetTexture(std::string name) {
	return textures[name];
}

AudioClip* AssetManager::GetSound(std::string name) {
	return sounds[name];
}

Material* AssetManager::GetMaterial(std::string name) {
	return materials[name];
}

void AssetManager::UnloadAll() {
	UnloadTextures();
	UnloadSounds();
	UnloadMaterials();
}

void AssetManager::UnloadTextures() {
	for (auto& [name, texture] : textures)
		texture->Unload();
}

void AssetManager::UnloadSounds() {
	for (auto& [name, clip] : sounds)
		clip->Unload();
}

void AssetManager::UnloadMaterials() {
	for (auto& [name, material] : materials)
		material->Unload();
}