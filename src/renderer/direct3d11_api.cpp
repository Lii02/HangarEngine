#include "Precompiled.h"
#include "direct3d11_api.h"
#include "platform/game_window.h"
#include "debug/assert.h"
#include <d3dcompiler.h>

extern "C" {
	HANGAR_API unsigned long NvOptimusEnablement = 0x00000001;
	HANGAR_API int AmdPowerXpressRequestHighPerformance = 1;
}

using namespace DirectX;

struct Direct3D11API::IRenderAPI::DataBuffer {
	ID3D11Buffer* buffer;
	size_t element_size;
	size_t element_count;

	~DataBuffer() {
		buffer->Release();
	}
};

struct Direct3D11API::IRenderAPI::RenderShader {
	ID3D11VertexShader* vertex_shader;
	ID3D11PixelShader* pixel_shader;
	ID3D11InputLayout* layout;
	std::string vertex_entry, pixel_entry;

	~RenderShader() {
		vertex_shader->Release();
		pixel_shader->Release();
		layout->Release();
	}
};

struct Direct3D11API::IRenderAPI::Texture2D {
	uint32_t slot, components, width, height;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* resource;

	~Texture2D() {
		texture->Release();
		resource->Release();
	}
};

Direct3D11API::Direct3D11API(GameWindow* _window_ptr)
	: IRenderAPI(_window_ptr) {
	initialize();
}

Direct3D11API::~Direct3D11API() {
	deinitialize();
}

void Direct3D11API::set_viewport() {
	D3D11_VIEWPORT vp;
	vp.Width = (float)window_ptr->get_width();
	vp.Height = (float)window_ptr->get_height();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = depth;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	device_context->RSSetViewports(1, &vp);
}

void Direct3D11API::initialize() {
}

void Direct3D11API::deinitialize() {
}

void Direct3D11API::begin_frame() {
}

void Direct3D11API::end_frame() {
}

uint64_t Direct3D11API::create_data_buffer(size_t data_size, size_t data_count, DataBufferBinding binding) {
	return uint64_t();
}

void Direct3D11API::update_data_buffer(uint64_t index, void* data) {
}

void Direct3D11API::remove_data_buffer(uint64_t index) {
}

void Direct3D11API::clean_data_buffers() {
}

void Direct3D11API::bind_vertex_byffer(uint64_t index) {
}

void Direct3D11API::bind_index_buffer(uint64_t index) {
}

void Direct3D11API::bind_constant_buffer(uint64_t index, uint32_t slot) {
}

void Direct3D11API::draw_indexed(uint32_t count, uint32_t first) {
}

void Direct3D11API::clean_shaders() {
}

uint64_t Direct3D11API::create_render_shader(std::string_view shader_source, std::string vertex_entry, std::string pixel_entry, std::vector<InputElement> inputs) {
	return uint64_t();
}

void Direct3D11API::bind_render_shader(uint64_t index) {
}

void Direct3D11API::remove_render_shader(uint64_t index) {
}

void Direct3D11API::set_topology(RenderTopology topology) {
}

float Direct3D11API::get_aspect_ratio() {
	return 0.0f;
}

std::string Direct3D11API::get_device_name() {
	return std::string();
}

uint64_t Direct3D11API::create_texture_2d(void* data, TextureFormat format, uint32_t width, uint32_t height, uint32_t slot) {
	return uint64_t();
}

void Direct3D11API::bind_texture_2d(uint64_t index) {
}

void Direct3D11API::remove_texture_2d(uint64_t index) {
}

void Direct3D11API::clean_textures() {
}