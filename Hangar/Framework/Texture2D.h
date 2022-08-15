#ifndef TEXTURE2D_H
#define TEXTURE2D_H

class Texture2D {
private:
	uint64_t index;
	uint32_t width, height, slot;
	TextureFormat format;
public:
	Texture2D(uint32_t width, uint32_t height, uint32_t slot, TextureFormat format);
	~Texture2D();

	void Initialize(void* data);
	void DeInitialize();
	void Bind();
};

#endif