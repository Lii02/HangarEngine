#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

struct ArgumentPacket {
	uint32_t argumentCount;
	char** arguments;
};

extern void Main(ArgumentPacket args);

#ifdef _DEBUG

#ifdef HANGAR_WINDOWS
	#pragma comment(linker, "/subsystem:console")
#endif

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Main({ static_cast<uint32_t>(argc), argv });
	return 0;
}
#else

#ifdef HANGAR_WINDOWS
	#pragma comment(linker, "/subsystem:windows")
#endif

extern "C" {
	int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		Main({ static_cast<uint32_t>(__argc), __argv });
		return 0;
	}
}
#endif

#endif