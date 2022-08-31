#ifndef SYSTEM_WINDOW_H
#define SYSTEM_WINDOW_H
#include "string/astring.h"

class SystemWindow {
public:
	struct Dimensions {
		uint32_t width;
		uint32_t height;
	};
protected:
	bool is_resizable, is_polling;
	AString title;
	Dimensions dimensions;
public:
	SystemWindow(AString _title, uint32_t _width, uint32_t _height, bool _is_resizable);
	virtual ~SystemWindow() { }

	bool get_is_resizable() const;
	bool is_running() const;
	AString get_title() const;
	virtual void set_is_resizable(bool _is_resizable);
	virtual Dimensions get_dimensions();
	virtual void set_dimensions(Dimensions new_dimensions);
	virtual void set_title(AString new_title);
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void poll() = 0;
	virtual void* get_window_handle() = 0;
	virtual bool is_focus() = 0;

	static SystemWindow* create(AString title, uint32_t width, uint32_t height, bool is_resizable);
};

#endif