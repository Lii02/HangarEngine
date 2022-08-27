#ifndef DIRECT3D11_API_H
#define DIRECT3D11_API_H
#include "irender_api.h"
#include <d3d11.h>
#include <dxgi1_2.h>

class Direct3D11API : public IRenderAPI {
	struct GPU {
		uint32_t index;
		DXGI_ADAPTER_DESC1 info;
		IDXGIAdapter1* adapter;
	};

	struct Monitor {
		uint32_t index;
		IDXGIOutput* output;
		DXGI_MODE_DESC* modes;
		uint32_t modeCount;
	};
private:
	ID3D11Device* device;
	ID3D11DeviceContext* device_context;
	IDXGIFactory2* factory;
	IDXGISwapChain* swapchain;
	ID3D11RenderTargetView* render_target_view;
	ID3D11DepthStencilView* depth_stencil_view;
	ID3D11RasterizerState* raster_state;
	ID3D11BlendState* blend_state;
	List<GPU> adapters;
	List<Monitor> monitors;
	D3D_FEATURE_LEVEL feature_level;
	GPU* selected_gpu;
public:
	Direct3D11API(GameWindow* _window_ptr);
	~Direct3D11API();

	virtual void initialize() override;
	virtual void deinitialize() override;
	virtual void begin_frame() override;
	virtual void end_frame() override;
	virtual uint64_t create_data_buffer(size_t data_size, size_t data_count, DataBufferBinding binding) override;
	virtual void update_data_buffer(uint64_t index, void* data) override;
	virtual void remove_data_buffer(uint64_t index) override;
	virtual void clean_data_buffers() override;
	virtual void bind_vertex_byffer(uint64_t index) override;
	virtual void bind_index_buffer(uint64_t index) override;
	virtual void bind_constant_buffer(uint64_t index, uint32_t slot) override;
	virtual void draw_indexed(uint32_t count, uint32_t first) override;
	virtual void clean_shaders() override;
	virtual uint64_t create_render_shader(std::string_view shader_source, std::string vertex_entry, std::string pixel_entry, List<InputElement> inputs) override;
	virtual void bind_render_shader(uint64_t index) override;
	virtual void remove_render_shader(uint64_t index) override;
	virtual void set_topology(RenderTopology topology) override;
	virtual float get_aspect_ratio() override;
	virtual std::string get_device_name() override;
	virtual uint64_t create_texture_2d(void* data, TextureFormat format, uint32_t width, uint32_t height, uint32_t slot) override;
	virtual void bind_texture_2d(uint64_t index) override;
	virtual void remove_texture_2d(uint64_t index) override;
	virtual void clean_textures() override;
private:
	void set_viewport();
};

#endif