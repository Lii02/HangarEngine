#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include "../IComponent.h"
#include "../../Math/Vectors.h"

class AudioClip;

class AudioSource : public IComponent {
private:
	unsigned int sourceID;
	float pitch, gain;
	bool loop;
	Vector3 velocity;
	AudioClip* clip;
public:
	AudioSource(float pitch, float gain, bool loop, Vector3 velocity);
	~AudioSource();

	void SetClip(AudioClip* clip);
	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

#endif