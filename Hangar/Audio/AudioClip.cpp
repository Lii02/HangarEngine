#include "Precompiled.h"
#include "AudioClip.h"
#include <Audio/AudioEngine.h>

AudioClip::AudioClip() {
	this->bufferID = AudioEngine::Get()->CreateBuffer();
}

AudioClip::~AudioClip() {
	AudioEngine::Get()->RemoveBuffer(bufferID);
}

void AudioClip::SetData(void* data, uint32_t format, uint32_t size, uint32_t frequency) {
	this->bufferSize = size;
	AudioEngine::Get()->BufferData(bufferID, data, format, size, frequency);
}

unsigned int AudioClip::GetID() const {
	return bufferID;
}