#include "Precompiled.h"
#include "IComponent.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/AudioListener.h"
#include "Components/AudioSource.h"

template <typename T>
inline constexpr ComponentType IComponent::TypeToEnum() { return ComponentType::UNKNOWN; }

#define REGISTER_COMPONENT(T, type) template<> ComponentType IComponent::TypeToEnum<T>() { return type; }

REGISTER_COMPONENT(Mesh, ComponentType::MESH)
REGISTER_COMPONENT(Camera, ComponentType::CAMERA)
REGISTER_COMPONENT(AudioListener, ComponentType::AUDIOLISTENER)
REGISTER_COMPONENT(AudioSource, ComponentType::AUDIOSOURCE)