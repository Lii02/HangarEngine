#ifndef AUDIOCLIP_H
#define AUDIOCLIP_H

class AudioClip {
private:
	unsigned int bufferID;
	size_t bufferSize;
public:
	AudioClip();
	~AudioClip();
	AudioClip(const AudioClip&) = delete;

	void SetData(void* data, uint32_t format, uint32_t size, uint32_t frequency);
	unsigned int GetID() const;
};

#endif