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
#include <Hangar/Framework/Components/AudioSource.h>
#include <Hangar/Audio/AudioClip.h>
#include <Hangar/Assets/WAVLoader.h>
#include <Hangar/Threading/ThreadPool.h>
#include <Hangar/Framework/Material.h>

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	FileSystem::Init();
	AudioEngine::Initialize();
	ThreadPool::Initialize();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Init(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler& profiler = Profiler::Get();
	Mouse& mouse = Mouse::Get();
	Keyboard& keyboard = Keyboard::Get();

	Logger::Message("Using device: " + RendererCommands::GetDeviceName());

	{
		Scene scene;
		auto cube = OBJLoader::Load(fs->ImmSearchFile("cube.obj"));

		AudioClip* clip = WAVLoader::Load(fs->ImmSearchFile("amulet.wav"));
		Entity* entity = new Entity;
		entity->AddComponent(new Mesh(&cube[0], cube[0].indices.size()));
		entity->AddComponent(new AudioSource(1.0f, 10.0f, false, Vector3()));
		entity->GetComponent<AudioSource>()->SetClip(clip);
		entity->GetTransform().position = Vector3(0, -5, 0);
		entity->GetTransform().scale = Vector3(10, 1, 10);
		scene.AddEntity(entity);

		Entity* camera = new Entity;
		camera->AddComponent(new Camera(90.0f, -0.1f, 1000.0f));
		camera->AddComponent(new AudioListener(1.0f, Vector3()));
		scene.AddEntity(camera);
		scene.SetMainCamera(camera);
		camera->GetTransform().position.z = -5;

		Material* material = new Material();
		material->SetDiffuse(MaterialAttribute<Color>(Color(1, 0, 0), MaterialAttributeType::COLOR_VALUE));
		material->Update();

		totalTime.Begin();
		const float speed = 10;
		while (window.IsRunning()) {
			profiler.ClearTotals();
			profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
			delta.Begin();

			RendererCommands::BeginFrame();
			scene.Render();
			material->Bind();
			RendererCommands::EndFrame();

			if (keyboard.GetKey(KeyCode::KEY_TAB)) {
				entity->GetComponent<AudioSource>()->Play();
			}

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

			delta.End();
			window.Poll();
			profiler.EndFunction();
		}

		delete material;
		delete clip;
	}

	ThreadPool::DeInitialize();
	AudioEngine::DeInitialize();
	FileSystem::DeInitialize();
	RendererCommands::DeInitialize();
}