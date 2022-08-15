#include "Precompiled.h"
#include "AudioListener.h"
#include <Audio/AudioEngine.h>
#include <Framework/Entity.h>

AudioListener::AudioListener(float gain, Vector3 velocity)
	: IComponent(ComponentType::AUDIOLISTENER) {
	this->gain = gain;
	this->velocity = velocity;
}

AudioListener::~AudioListener() {
}

void AudioListener::Init() {
}

void AudioListener::Render() {
}

void AudioListener::Update() {
	Vector3 orientation[2] = { Vector3(0, 0, -1), Vector3(0, 1, 0) };
	AudioEngine::Get().SetListenerData(gain, GetEntity()->GetTransform().position, velocity, orientation);
}