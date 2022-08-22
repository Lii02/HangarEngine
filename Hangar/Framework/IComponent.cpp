#include "Precompiled.h"
#include "IComponent.h"
#include "Components/MeshRenderer.h"
#include "Components/Camera.h"
#include "Components/AudioListener.h"
#include "Components/AudioSource.h"
#include "Components/Light.h"

template <typename T>
inline constexpr ComponentType IComponent::TypeToEnum() { return ComponentType::UNKNOWN; }

#define REGISTER_COMPONENT(T, type) template<> ComponentType IComponent::TypeToEnum<T>() { return type; }

REGISTER_COMPONENT(MeshRenderer, ComponentType::MESHRENDERER)
REGISTER_COMPONENT(Camera, ComponentType::CAMERA)
REGISTER_COMPONENT(AudioListener, ComponentType::AUDIOLISTENER)
REGISTER_COMPONENT(AudioSource, ComponentType::AUDIOSOURCE)
REGISTER_COMPONENT(Light, ComponentType::LIGHT)