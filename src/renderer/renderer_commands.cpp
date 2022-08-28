#include "precompiled.h"
#include "renderer_commands.h"
#include "direct3d11_api.h"

namespace {
	RendererType g_RendererType;
	IRenderAPI* g_RendererAPI = nullptr;
}

RendererType RendererCommands::get_api() {
	return g_RendererType;
}

uint64_t RendererCommands::get_object_draw_count() {
	return g_RendererAPI->get_object_draw_count();
}

uint64_t RendererCommands::get_vertex_draw_count() {
	return g_RendererAPI->get_vertex_draw_count();
}