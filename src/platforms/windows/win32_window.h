#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H
#include "os/system_window.h"
#include <windows.h>

class Win32Window : public SystemWindow {
private:
	HWND handle;
public:
	Win32Window();
	~Win32Window();

	virtual void set_is_resizable(bool _is_resizable) override;
	virtual Dimensions get_dimensions() override;
	virtual void set_dimensions(Dimensions new_dimensions) override;
	virtual void set_title(AString new_title) override;
	virtual void open() override;
	virtual void close() override;
	virtual void poll() override;
	virtual void* get_window_handle() override;
};

#endif