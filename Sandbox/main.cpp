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
#include <Hangar/Framework/Entity.h>
#include <Hangar/Framework/Components/Mesh.h>

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	FileSystem::Init();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Init(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler& profiler = Profiler::Get();

	{
		File* shaderFile = fs->ImmSearchFile("test.hlsl");
		shaderFile->Open();
		InputElementArray inputElements;
		inputElements.push_back({ 0, 3, 0, "POSITION" });
		inputElements.push_back({ 0, 2, 0, "TEXCOORD" });
		inputElements.push_back({ 0, 3, 0, "NORMAL" });

		uint64_t shader = RendererCommands::CreateRenderShader(shaderFile->ReadString(shaderFile->Length()), "VS", "PS", inputElements);

		Mesh::Vertices vertices = {
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, {0, 0, 0}},
			{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}, {0, 0, 0}},
			{{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}, {0, 0, 0}},
			{{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}, {0, 0, 0}}
		};

		Mesh::Indices indices = {
			0, 1, 2, 0, 2, 3,
		};
		Entity entity;
		entity.AddComponent(new Mesh(&vertices, &indices, 6));

		totalTime.Begin();
		while (window.IsRunning()) {
			profiler.ClearTotals();
			profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
			delta.Begin();
			RendererCommands::BeginFrame();

			RendererCommands::BindRenderShader(shader);
			entity.Render();
			entity.Update();

			RendererCommands::EndFrame();
			delta.End();
			window.Poll();
			profiler.EndFunction();
		}
	}

	FileSystem::DeInitialize();
	RendererCommands::DeInitialize();
}