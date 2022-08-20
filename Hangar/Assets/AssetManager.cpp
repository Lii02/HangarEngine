#include "Precompiled.h"
#include "AssetManager.h"

namespace {
	AssetManager g_AssetManager;
}

AssetManager& AssetManager::Get() {
	return g_AssetManager;
}

AssetManager::AssetManager() {
}

AssetManager::~AssetManager() {
}