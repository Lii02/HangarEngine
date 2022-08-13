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
#include <Hangar/Framework/EntityRenderer.h>

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	FileSystem::Init();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Init(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler& profiler = Profiler::Get();

	{
		EntityRenderer renderer = EntityRenderer(90.0f, 0.1f, 1000.0f);
		
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
		entity.GetTransform().position.z = 1;
		
		totalTime.Begin();
		while (window.IsRunning()) {
			profiler.ClearTotals();
			profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
			delta.Begin();
			RendererCommands::BeginFrame();
			renderer.PrepareFrame();

			renderer.DrawEntity(&entity);
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