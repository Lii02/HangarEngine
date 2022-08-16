#ifndef ENTITY_H
#define ENTITY_H
#include "IComponent.h"
#include "Identifier.h"
#include "Transform.h"
#include "Material.h"

enum class RendererUsage {
	NONE,
	ENTITYRENDERER,
};

typedef std::bitset<24> ComponentMask;

class Entity {
	friend class IComponent;
private:
	std::string name;
	Identifier identifier;
	Transform transform;
	bool active;
	std::vector<IComponent*> components;
	ComponentMask componentMask;
	RendererUsage rendererUsage;
	Material* material;
public:
	Entity(std::string name = "Entity");
	~Entity();

	void AddComponent(IComponent* component);
	void RemoveComponents();
	void RemoveComponent(uint32_t index);
	IComponent* GetComponent(uint32_t index);
	void Render();
	void Update();
	std::string GetName() const;
	bool IsActive() const;
	void SetActive(bool active);
	Identifier GetIdentifier();
	Transform& GetTransform();
	bool HasComponent(ComponentType type) const;
	template <typename T>
	T* GetComponent() {
		ComponentType type = IComponent::TypeToEnum<T>();
		if (!HasComponent(type))
			return nullptr;
		
		for (auto& component : components) {
			if (component->type == type)
				return dynamic_cast<T*>(component);
		}
		return nullptr;
	}
	RendererUsage GetRendererUsage() const;
	void SetRendererUsage(RendererUsage rendererUsage);
	Material* GetMaterial();
	void SetMaterial(Material* newMaterial);
private:
	bool GetComponentMask(size_t maskType) const;
};

#endif