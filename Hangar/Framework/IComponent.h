#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class Entity;

enum ComponentType : int32_t {
	UNKNOWN = -1,
	MESH = HANGAR_BIT(0),
	CAMERA = HANGAR_BIT(1),
};

class IComponent {
	friend class Entity;
private:
	Entity* entity;
	bool enabled;
	ComponentType type;
public:
	IComponent(ComponentType type) : type(type) { }
	virtual ~IComponent() { }
	IComponent(const IComponent&) = delete;

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	Entity* GetEntity() { return entity; }
	bool IsEnabled() const { return enabled; }
	void SetEnabled(bool enabled) { this->enabled = enabled; }
	ComponentType GetType() const { return type; }
	template <typename T>
	static constexpr ComponentType TypeToEnum();
};

#endif