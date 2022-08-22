#include <Hangar/HangarEngine.h>

void Main(ArgumentPacket args) {
	Logger::Initialize();
	FileSystem::Initialize();
	GameWindow window = GameWindow("Hangar Engine", 1600, 900, false);
	window.Open();
	AudioEngine::Initialize();
	ThreadPool::Initialize();
	Profiler::Initialize();
	Mouse::Initialize();
	Keyboard::Initialize();
	AssetManager::Initialize();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Inititialize(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler*& profiler = Profiler::Get();
	Mouse*& mouse = Mouse::Get();
	Keyboard*& keyboard = Keyboard::Get();

	Logger::Message("Using device: " + RendererCommands::GetDeviceName());

	Scene* scene = new Scene();

	Entity* camera = new Entity;
	camera->AddComponent(new Camera(90.0f, 0.01f, FLT_MAX));
	camera->AddComponent(new AudioListener(1.0f, Vector3()));
	scene->AddEntity(camera);
	scene->SetMainCamera(camera);
	camera->GetTransform().position.z = -5;
	camera->GetTransform().position.y = 2;

	totalTime.Begin();
	const float speed = 10;
	while (window.IsRunning()) {
		profiler->ClearTotals();
		profiler->BeginProfile("Main", ProfilerElementCategory::RENDER);
		delta.Begin();

		RendererCommands::BeginFrame();
		scene->Render();
		RendererCommands::EndFrame();

		scene->Update();
		if (keyboard->GetKey(KeyCode::KEY_W)) {
			camera->GetTransform().position.z += speed * delta.GetDeltaSeconds();
		} if (keyboard->GetKey(KeyCode::KEY_S)) {
			camera->GetTransform().position.z -= speed * delta.GetDeltaSeconds();
		} if (keyboard->GetKey(KeyCode::KEY_A)) {
			camera->GetTransform().position.x -= speed * delta.GetDeltaSeconds();
		} if (keyboard->GetKey(KeyCode::KEY_D)) {
			camera->GetTransform().position.x += speed * delta.GetDeltaSeconds();
		}

		delta.End();
		window.Poll();
		profiler->EndFunction();
	}

	delete scene;
	RendererCommands::DeInitialize();
	AssetManager::DeInitialize();
	Keyboard::DeInitialize();
	Mouse::DeInitialize();
	Profiler::DeInitialize();
	ThreadPool::DeInitialize();
	AudioEngine::DeInitialize();
	FileSystem::DeInitialize();
	Logger::DeInitialize();
}