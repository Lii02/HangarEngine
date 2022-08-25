#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

class AudioClip;
class Material;
class Texture2D;
class Mesh;

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

	void AddTexture(std::string name, Texture2D* texture);
	void AddSound(std::string name, AudioClip* sound);
	void AddMaterials(std::string name, Material* material);
	Texture2D* GetTexture(std::string name);
	AudioClip* GetSound(std::string name);
	Material* GetMaterial(std::string name);
	void UnloadAll();
	void UnloadTextures();
	void UnloadSounds();
	void UnloadMaterials();
};

#endif