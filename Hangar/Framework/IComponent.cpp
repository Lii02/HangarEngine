#include "Precompiled.h"
#include "IComponent.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"

template <typename T>
inline constexpr ComponentType IComponent::TypeToEnum() { return ComponentType::UNKNOWN; }

#define REGISTER_COMPONENT(T, type) template<> ComponentType IComponent::TypeToEnum<T>() { return type; }

REGISTER_COMPONENT(Mesh, ComponentType::MESH)
REGISTER_COMPONENT(Camera, ComponentType::CAMERA)