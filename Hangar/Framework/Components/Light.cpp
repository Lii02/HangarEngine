#include "Precompiled.h"
#include "Light.h"

Light::Light(Vector3 color, float intensity, LightType type) 
	: IComponent(ComponentType::LIGHT) {
	this->color = color;
	this->intensity = intensity;
	this->type = type;
}

void Light::Initialize() {
}

void Light::Render() {
}

void Light::Update() {
}

Vector3 Light::GetColor() const {
	return color;
}

float Light::GetIntensity() const {
	return intensity;
}

LightType Light::GetType() const {
	return type;
}
