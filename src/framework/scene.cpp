#include "Precompiled.h"
#include "Scene.h"
#include "EntityRenderer.h"
#include "Components/Camera.h"

Scene::Scene(std::string sceneName) {
	this->sceneName = sceneName;
	Initialize();
}

Scene::~Scene() {
	delete entityRenderer;
	ClearObjects();
}

void Scene::Initialize() {
	this->entityRenderer = new EntityRenderer();
}

void Scene::Render() {
	entityRenderer->PrepareFrame(mainCamera, mainCamera->GetComponent<Camera>()->GetProjection());
	for (auto& e : entities) {
		if (e.second->IsActive()) {
			switch (e.second->GetSelectedRenderer()) {
			case SelectedRenderer::ENTITYRENDERER:
				entityRenderer->DrawEntity(e.second);
				break;
			}
		}
	}
}

void Scene::Update() {
	for (auto& e : entities) {
		if(e.second->IsActive())
			e.second->Update();
	}
}

void Scene::AddEntity(Entity* e) {
	entities.emplace(std::make_pair(e->GetIdentifier(), e));
}

void Scene::RemoveEntity(std::string name) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if (it->second->GetName() == name)
			entities.erase(it);
	}
}

Entity* Scene::GetEntity(std::string name) {
	for (auto& e : entities) {
		if (e.second->GetName() == name)
			return e.second;
	}
	return nullptr;
}

Entity* Scene::GetEntity(Identifier id) {
	return entities[id];
}

void Scene::ClearObjects() {
	for (auto& e : entities) {
		delete e.second;
	}
	entities.clear();
}

void Scene::SetMainCamera(Entity* e) {
	this->mainCamera = e;
}

Entity* Scene::GetMainCamera() {
	return mainCamera;
}