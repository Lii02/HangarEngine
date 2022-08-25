#ifndef AUDIOLISTENER_H
#define AUDIOLISTENER_H
#include "../IComponent.h"
#include "../../Math/Vectors.h"

class AudioListener : public IComponent {
private:
	float gain;
	Vector3 velocity;
public:
	AudioListener(float gain, Vector3 velocity);
	~AudioListener();

	virtual void Initialize() override;
	virtual void Render() override;
	virtual void Update() override;
};

#endif