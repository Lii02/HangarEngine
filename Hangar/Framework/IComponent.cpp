#include "Precompiled.h"
#include "IComponent.h"
#include "Components/Mesh.h"

template <typename T>
inline constexpr ComponentType IComponent::TypeToEnum() { return ComponentType::Unknown; }

#define REGISTER_COMPONENT(T, type) template<> ComponentType IComponent::TypeToEnum<T>() { return type; }

REGISTER_COMPONENT(Mesh, ComponentType::MESH)