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

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	FileSystem::Init();
	FileSystem*& fs = FileSystem::Get();
	RendererCommands::Init(RendererType::DIRECTX11, &window);
	Stopwatch delta, totalTime;
	Profiler& profiler = Profiler::Get();

	totalTime.Begin();
	while (window.IsRunning()) {
		profiler.ClearTotals();
		profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
		delta.Begin();
		RendererCommands::BeginFrame();
		
		RendererCommands::EndFrame();
		delta.End();
		window.Poll();
		profiler.EndFunction();
	}

	FileSystem::DeInitialize();
	RendererCommands::DeInitialize();
}