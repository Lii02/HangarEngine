#include "Precompiled.h"
#include "Entity.h"
#include "../Debug/Logger.h"

Entity::Entity(std::string name) {
	this->name = name;
	this->active = true;
	this->componentMask = 0;
	this->rendererUsage = RendererUsage::ENTITYRENDERER;
	identifier.Generate();
}

Entity::~Entity() {
	RemoveComponents();
}

void Entity::AddComponent(IComponent* component) {
	if (HasComponent(component->type)) {
		Logger::Warning(name + " already has component type: " + std::to_string(component->type));
		return;
	}
	component->entity = this;
	component->enabled = true;
	componentMask.set(component->type, true);
	component->Init();
	components.push_back(component);
}

void Entity::RemoveComponents() {
	for (auto& component : components) {
		delete component;
	}
	components.clear();
	componentMask.reset();
}

void Entity::RemoveComponent(uint32_t index) {
	auto& component = components[index];
	components.erase(components.begin() + index);
	componentMask.set(component->type, false);
	delete component;
}

void Entity::Render() {
	for (auto& component : components) {
		if(component->IsEnabled())
			component->Render();
	}
}

IComponent* Entity::GetComponent(uint32_t index) {
	return components[index];
}

void Entity::Update() {
	for (auto& component : components) {
		if (component->IsEnabled())
			component->Update();
	}
}

Transform& Entity::GetTransform() {
	return transform;
}

RendererUsage Entity::GetRendererUsage() const {
	return rendererUsage;
}

bool Entity::GetComponentMask(size_t maskType) const {
	return componentMask.test(maskType);
}

void Entity::SetRendererUsage(RendererUsage rendererUsage) {
	this->rendererUsage = rendererUsage;
}

std::string Entity::GetName() const {
	return name;
}

bool Entity::IsActive() const {
	return active;
}

void Entity::SetActive(bool active) {
	this->active = active;
}

Identifier Entity::GetIdentifier() {
	return identifier;
}

bool Entity::HasComponent(ComponentType type) const {
	return GetComponentMask(type);
}