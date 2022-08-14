#include <Hangar/Precompiled.h>
#include <Hangar/Platform/EntryPoint.h>
#include <Hangar/Platform/GameWindow.h>
#include <Hangar/Platform/Mouse.h>
#include <Hangar/Platform/Keyboard.h>
#include <Hangar/Debug/Logger.h>
#include <Hangar/Debug/Assert.h>
#include <Hangar/Renderer/RendererCommands.h>
#include <Hangar/IO/FileSystem.h>
#include <Hangar/Framework/Stopwatch.h>
#include <Hangar/Profiler/Profiler.h>
#include <Hangar/Framework/Components/Mesh.h>
#include <Hangar/Framework/Components/Camera.h>
#include <Hangar/Framework/Scene.h>
#include <Hangar/Assets/OBJLoader.h>

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	FileSystem::Init();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Init(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler& profiler = Profiler::Get();

	Logger::Message("Using device: " + RendererCommands::GetDeviceName());

	{
		Scene scene;

		auto cube = OBJLoader::Load(fs->ImmSearchFile("monkey.obj"));

		Entity* entity = new Entity;
		entity->AddComponent(new Mesh(&cube[0], cube[0].indices.size()));
		scene.AddEntity(entity);

		Entity* camera = new Entity;
		camera->AddComponent(new Camera(90.0f, 0.1f, 100.0f));
		scene.AddEntity(camera);
		scene.SetMainCamera(camera);
		camera->GetTransform().position.z = -5;

		totalTime.Begin();
		while (window.IsRunning()) {
			profiler.ClearTotals();
			profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
			delta.Begin();
			RendererCommands::BeginFrame();

			entity->GetTransform().rotation.y++;
			scene.Render();
			scene.Update();

			RendererCommands::EndFrame();
			delta.End();
			window.Poll();
			profiler.EndFunction();
		}
	}

	FileSystem::DeInitialize();
	RendererCommands::DeInitialize();
}