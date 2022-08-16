#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture2D.h"

class TextureManager {
private:
	std::unordered_map<std::string, Texture2D*> textures;
public:
	static TextureManager& Get();

	TextureManager();
	~TextureManager();

	void AddTexture(std::string name, Texture2D* texture);
	void CleanTextures();
	const Texture2D* GetTexture(std::string name);
	void RemoveTexture(std::string name);
};

#endif