#ifndef RENDER_API_H
#define RENDER_API_H
#include "containers/list.h"
#include "string/astring.h"

class GameWindow;

enum class DataBufferBinding {
	VERTEX_BUFFER,
	INDEX_BUFFER,
	CONSTANT_BUFFER
};

enum class RenderTopology {
	LINES,
	TRIANGLES,
	POINTS,
};

enum class TextureFormat {
	R8G8B8A8,
};

struct InputElement {
	int index, numFloats, offset;
	AString name;
};

typedef List<InputElement> InputElementArray;

class IRenderAPI {
protected:
	void* window_ptr;
	uint64_t object_draw_count; // # of objects being draw
	uint64_t vertex_draw_count; // # of vertices being draw
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float depth;
	bool vsync;
	struct DataBuffer;
	List<DataBuffer*> data_buffers;
	struct RenderShader;
	List<RenderShader*> render_shaders;
	struct Texture2D;
	List<Texture2D*> textures;
public:
	IRenderAPI(void* _window_ptr) : window_ptr(_window_ptr), object_draw_count(0), vertex_draw_count(0), depth(1.0f), vsync(true) { }
	virtual ~IRenderAPI() { }
	IRenderAPI(const IRenderAPI&) = delete;

	virtual void initialize() = 0;
	virtual void deinitialize() = 0;
	virtual void begin_frame() = 0;
	virtual void end_frame() = 0;
	virtual uint64_t create_data_buffer(size_t data_size, size_t data_count, DataBufferBinding binding) = 0;
	virtual void update_data_buffer(uint64_t index, void* data) = 0;
	virtual void remove_data_buffer(uint64_t index) = 0;
	virtual void clean_data_buffers() = 0;
	virtual void bind_vertex_byffer(uint64_t index) = 0;
	virtual void bind_index_buffer(uint64_t index) = 0;
	virtual void bind_constant_buffer(uint64_t index, uint32_t slot) = 0;
	virtual void draw_indexed(uint32_t count, uint32_t first) = 0;
	virtual void clean_shaders() = 0;
	virtual uint64_t create_render_shader(AString shader_source, AString vertex_entry, AString pixel_entry, List<InputElement> inputs) = 0;
	virtual void bind_render_shader(uint64_t index) = 0;
	virtual void remove_render_shader(uint64_t index) = 0;
	virtual void set_topology(RenderTopology topology) = 0;
	virtual float get_aspect_ratio() = 0;
	virtual AString get_device_name() = 0;
	virtual uint64_t create_texture_2d(void* data, TextureFormat format, uint32_t width, uint32_t height, uint32_t slot) = 0;
	virtual void bind_texture_2d(uint64_t index) = 0;
	virtual void remove_texture_2d(uint64_t index) = 0;
	virtual void clean_textures() = 0;

	void clear_stats() {
		object_draw_count = 0;
		vertex_draw_count = 0;
	}
	inline bool is_vsync_enabled() const { return vsync; }
	inline void set_clear_color(float _clear_color[4]) { memcpy(clear_color, _clear_color, sizeof(float) * 4); }
	inline void set_depth(float _depth) { depth = _depth; }
	inline void set_vsync(bool _vsync) { vsync = _vsync; }
	inline uint64_t get_object_draw_count() const { return object_draw_count; };
	inline uint64_t get_vertex_draw_count() const { return vertex_draw_count; };
};

#endif