#ifndef RENDERER_COMMANDS_H
#define RENDERER_COMMANDS_H
#include "irender_api.h"

enum class RendererType {
	DIRECTX11,
};

class GameWindow;

class RendererCommands {
public:
	static RendererType get_api();

	static uint64_t get_object_draw_count();
	static uint64_t get_vertex_draw_count();
};

#endif