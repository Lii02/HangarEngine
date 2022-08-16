#ifndef LIGHT_H
#define LIGHT_H
#include "../IComponent.h"
#include "../../Math/Vectors.h"

enum LightType : int {
	POINTLIGHT = 0,
	DIRECTIONALLIGHT = 1,
	SPOTLIGHT = 2
};

class Light : public IComponent {
private:
	Vector3 color;
	float intensity;
	LightType type;
public:
	Light(Vector3 color, float intensity, LightType type);

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
	Vector3 GetColor() const;
	float GetIntensity() const;
	LightType GetType() const;
};

#endif