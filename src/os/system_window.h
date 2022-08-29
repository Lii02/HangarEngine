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
	bool is_running, is_resizable;
private:
	AString title;
	Dimensions dimensions;
public:
	virtual ~SystemWindow() { }

	bool get_is_resizable() const;
	bool get_is_running() const;
	AString get_title() const;
	virtual void set_is_resizable(bool _is_resizable);
	virtual Dimensions get_dimensions();
	virtual void set_dimensions(Dimensions new_dimensions);
	virtual void set_title(AString new_title);
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void poll() = 0;
	virtual void* get_window_handle() = 0;
};

#endif