#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include <AL/alc.h>
#include "math/vectors.h"

class AudioEngine {
private:
	ALCdevice* device;
	ALCcontext* context;
	std::vector<unsigned int> sources;
	std::vector<unsigned int> buffers;
public:
	static void initialize();
	static void deinitialize();
	static AudioEngine*& get();

	AudioEngine();
	~AudioEngine();
	AudioEngine(const AudioEngine&) = delete;

	void clean_sources();
	void clean_buffers();
	unsigned int create_source();
	unsigned int create_buffer();
	void remove_source(unsigned int sourceID);
	void remove_buffer(unsigned int bufferID);
	void set_listener_data(float gain, Vector3 position, Vector3 velocity, Vector3 orientation[2]);
	void set_source_clip(unsigned int sourceID, unsigned int bufferID);
	void play_source(unsigned int sourceID);
	void stop_source(unsigned int sourceID);
	void pause_source(unsigned int sourceID);
	void rewind_source(unsigned int sourceID);
	void set_source_info(unsigned int sourceID, float pitch, float gain, Vector3 position, Vector3 velocity, bool loop);
	bool is_playing(unsigned int sourceID);
	void buffer_data(unsigned int bufferID, void* data, uint32_t format, uint32_t size, uint32_t frequency);
	
	static uint32_t get_format(uint16_t channels, uint16_t samples);
};

#endif