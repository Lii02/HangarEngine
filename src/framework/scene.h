#ifndef SCENE_H
#define SCENE_H
#include "Entity.h"

class EntityRenderer;

class Scene {
private:
	std::string sceneName;
	std::map<Identifier, Entity*> entities;
	EntityRenderer* entityRenderer;
	Entity* mainCamera;
public:
	Scene(std::string sceneName = "Scene");
	~Scene();

	void Initialize();
	void Render();
	void Update();
	void AddEntity(Entity* e);
	void RemoveEntity(std::string name);
	Entity* GetEntity(std::string name);
	Entity* GetEntity(Identifier id);
	void ClearObjects();
	void SetMainCamera(Entity* e);
	Entity* GetMainCamera();
};

#endif