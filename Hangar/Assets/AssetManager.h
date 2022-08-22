#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

class AudioClip;
class Material;
class Texture2D;

class AssetManager {
private:
	std::unordered_map<std::string, Texture2D*> textures;
	std::unordered_map<std::string, AudioClip*> sounds;
	std::unordered_map<std::string, Material*> materials;
public:
	static AssetManager*& Get();
	static void Initialize();
	static void DeInitialize();

	AssetManager();
	~AssetManager();
};

#endif