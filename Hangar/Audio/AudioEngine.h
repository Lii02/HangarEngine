#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include <AL/alc.h>
#include "../Math/Vectors.h"

class AudioEngine {
private:
	ALCdevice* device;
	ALCcontext* context;
	std::vector<unsigned int> sources;
	std::vector<unsigned int> buffers;
public:
	static AudioEngine& Get();

	AudioEngine();
	~AudioEngine();
	AudioEngine(const AudioEngine&) = delete;

	void Initialize();
	void DeInitialize();
	void CleanSources();
	void CleanBuffers();
	unsigned int CreateSource();
	unsigned int CreateBuffer();
	void RemoveSource(unsigned int sourceID);
	void RemoveBuffer(unsigned int bufferID);
	void SetListenerData(float gain, Vector3 position, Vector3 velocity, Vector3 orientation[2]);
	void SetSourceClip(unsigned int sourceID, unsigned int bufferID);
	void PlaySource(unsigned int sourceID);
	void StopSource(unsigned int sourceID);
	void PauseSource(unsigned int sourceID);
	void RewindSource(unsigned int sourceID);
	void SetSourceInfo(unsigned int sourceID, float pitch, float gain, Vector3 position, Vector3 velocity, bool loop);
	bool IsPlaying(unsigned int sourceID);
	void BufferData(unsigned int bufferID, void* data, uint32_t format, uint32_t size, uint32_t frequency);
	
	static uint32_t GetFormat(uint16_t channels, uint16_t samples);
};

#endif