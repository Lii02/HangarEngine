#include "Precompiled.h"
#include "AssetManager.h"

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
}