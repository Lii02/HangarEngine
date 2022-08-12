#include <Hangar/Precompiled.h>
#include <Hangar/Platform/EntryPoint.h>
#include <Hangar/Platform/GameWindow.h>
#include <Hangar/Platform/Mouse.h>
#include <Hangar/Platform/Keyboard.h>
#include <Hangar/Debug/Logger.h>
#include <Hangar/Debug/Assert.h>
#include <Hangar/Renderer/Direct3D11API.h>
#include <Hangar/IO/FileSystem.h>
#include <Hangar/Framework/Stopwatch.h>
#include <Hangar/Profiler/Profiler.h>

void Main(ArgumentPacket args) {
	GameWindow window = GameWindow("Hangar Engine", 1280, 720, false);
	window.Open();
	IRenderAPI* renderApi = new Direct3D11API(&window);
	Stopwatch delta;
	Profiler& profiler = Profiler::Get();

	while (window.IsRunning()) {
		profiler.ClearTotals();
		profiler.BeginProfile("Main", ProfilerElementCategory::RENDER);
		delta.Begin();
		renderApi->BeginFrame();
		
		renderApi->EndFrame();
		delta.End();
		window.Poll();
		profiler.EndFunction();
	}

	delete renderApi;
}