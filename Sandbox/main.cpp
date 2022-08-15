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
#include <Hangar/Audio/AudioEngine.h>
#include <Hangar/Framework/Components/AudioListener.h>

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	FileSystem::Init();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Init(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler& profiler = Profiler::Get();
	Mouse& mouse = Mouse::Get();
	Keyboard& keyboard = Keyboard::Get();

	Logger::Message("Using device: " + RendererCommands::GetDeviceName());

	{
		Scene scene;

		auto cube = OBJLoader::Load(fs->ImmSearchFile("mosin9130.obj"));

		for (MeshData3D& mesh : cube) {
			Entity* entity = new Entity;
			entity->AddComponent(new Mesh(&mesh, mesh.indices.size()));
			scene.AddEntity(entity);
		}

		Entity* camera = new Entity;
		camera->AddComponent(new Camera(90.0f, 0.1f, 1000.0f));
		camera->AddComponent(new AudioListener(1.0f, Vector3()));
		scene.AddEntity(camera);
		scene.SetMainCamera(camera);
		camera->GetTransform().position.z = -5;

		totalTime.Begin();
		const float speed = 10;
		while (window.IsRunning()) {
			profiler.ClearTotals();
			profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
			delta.Begin();
			RendererCommands::BeginFrame();

			scene.Render();
			scene.Update();

			if (keyboard.GetKey(KeyCode::KEY_W)) {
				camera->GetTransform().position.z += speed * delta.GetDeltaSeconds();
			} if (keyboard.GetKey(KeyCode::KEY_S)) {
				camera->GetTransform().position.z -= speed * delta.GetDeltaSeconds();
			} if (keyboard.GetKey(KeyCode::KEY_A)) {
				camera->GetTransform().position.x -= speed * delta.GetDeltaSeconds();
			} if (keyboard.GetKey(KeyCode::KEY_D)) {
				camera->GetTransform().position.x += speed * delta.GetDeltaSeconds();
			}

			RendererCommands::EndFrame();
			delta.End();
			window.Poll();
			profiler.EndFunction();
		}
	}

	FileSystem::DeInitialize();
	RendererCommands::DeInitialize();
}