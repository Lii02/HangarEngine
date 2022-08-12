#include "Precompiled.h"
#include "Entity.h"

Entity::Entity(std::string name) {
	this->name = name;
	this->active = true;
	this->componentMask = 0;
}

Entity::~Entity() {
	RemoveComponents();
}

void Entity::AddComponent(IComponent* component) {
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
		component->Render();
	}
}

IComponent* Entity::GetComponent(uint32_t index) {
	return components[index];
}

void Entity::Update() {
	for (auto& component : components) {
		component->Update();
	}
}

bool Entity::GetComponentMask(size_t maskType) const {
	return componentMask.test(maskType);
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

bool Entity::HasComponent(ComponentType type) const {
	return GetComponentMask(type);
}