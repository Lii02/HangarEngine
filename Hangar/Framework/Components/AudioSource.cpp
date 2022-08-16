#include "Precompiled.h"
#include "AudioSource.h"
#include <Audio/AudioEngine.h>
#include <Framework/Entity.h>
#include <Audio/AudioClip.h>

AudioSource::AudioSource(float pitch, float gain, bool loop, Vector3 velocity)
	: IComponent(ComponentType::AUDIOSOURCE) {
	this->pitch = pitch;
	this->gain = gain;
	this->loop = loop;
	this->velocity = velocity;
	this->clip = nullptr;
}

AudioSource::~AudioSource() {
	AudioEngine::Get()->RemoveSource(sourceID);
}

void AudioSource::SetClip(AudioClip* clip) {
	this->clip = clip;
	AudioEngine::Get()->SetSourceClip(sourceID, clip->GetID());
}

void AudioSource::Play() {
	AudioEngine::Get()->PlaySource(sourceID);
}

void AudioSource::Stop() {
	AudioEngine::Get()->StopSource(sourceID);
}

bool AudioSource::IsPlaying() const {
	return AudioEngine::Get()->IsPlaying(sourceID);
}

void AudioSource::Init() {
	this->sourceID = AudioEngine::Get()->CreateSource();
}

void AudioSource::Render() {
}

void AudioSource::Update() {
	AudioEngine::Get()->SetSourceInfo(sourceID, pitch, gain, GetEntity()->GetTransform().position, velocity, loop);
}