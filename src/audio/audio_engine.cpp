#include "precompiled.h"
#include "audio_engine.h"
#include <AL/al.h>

namespace {
	AudioEngine* g_AudioEngine;
}

void AudioEngine::initialize() {
	g_AudioEngine = new AudioEngine();
}

void AudioEngine::deinitialize() {
	delete g_AudioEngine;
}

AudioEngine*& AudioEngine::get() {
	return g_AudioEngine;
}

AudioEngine::AudioEngine() {
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
}

AudioEngine::~AudioEngine() {
	clean_buffers();
	clean_sources();
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioEngine::clean_sources() {
	alDeleteSources(sources.size(), sources.data());
	sources.clear();
}

void AudioEngine::clean_buffers() {
	alDeleteBuffers(buffers.size(), buffers.data());
	buffers.clear();
}

unsigned int AudioEngine::create_source() {
	unsigned int source;
	alGenSources(1, &source);
	sources.push_back(source);
	return source;
}

unsigned int AudioEngine::create_buffer() {
	unsigned int buffer;
	alGenBuffers(1, &buffer);
	buffers.push_back(buffer);
	return buffer;
}

void AudioEngine::remove_source(unsigned int sourceID) {
	auto it = std::find(sources.begin(), sources.end(), sourceID);
	alDeleteSources(1, &sourceID);
	sources.erase(it);
}

void AudioEngine::remove_buffer(unsigned int bufferID) {
	auto it = std::find(buffers.begin(), buffers.end(), bufferID);
	alDeleteBuffers(1, &bufferID);
	buffers.erase(it);
}

void AudioEngine::set_listener_data(float gain, Vector3 position, Vector3 velocity, Vector3 orientation[2]) {
	alListenerf(AL_GAIN, gain);
	alListener3f(AL_POSITION, position.x, position.y, position.z);
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	alListenerfv(AL_ORIENTATION, (const float*)&orientation);
}

void AudioEngine::set_source_clip(unsigned int sourceID, unsigned int bufferID) {
	alSourcei(sourceID, AL_BUFFER, bufferID);
}

void AudioEngine::play_source(unsigned int sourceID) {
	alSourcePlay(sourceID);
}

void AudioEngine::stop_source(unsigned int sourceID) {
	alSourceStop(sourceID);
}

void AudioEngine::pause_source(unsigned int sourceID) {
	alSourcePause(sourceID);
}

void AudioEngine::rewind_source(unsigned int sourceID) {
	alSourceRewind(sourceID);
}

void AudioEngine::set_source_info(unsigned int sourceID, float pitch, float gain, Vector3 position, Vector3 velocity, bool loop) {
	alSourcef(sourceID, AL_PITCH, pitch);
	alSourcef(sourceID, AL_GAIN, gain);
	alSource3f(sourceID, AL_POSITION, position.x, position.y, position.z);
	alSource3f(sourceID, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	alSourcei(sourceID, AL_LOOPING, loop);
}

bool AudioEngine::is_playing(unsigned int sourceID) {
	int state;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

void AudioEngine::buffer_data(unsigned int bufferID, void* data, uint32_t format, uint32_t size, uint32_t frequency) {
	alBufferData(bufferID, format, data, size, frequency);
}

uint32_t AudioEngine::get_format(uint16_t channels, uint16_t samples) {
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}