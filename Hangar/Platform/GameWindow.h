#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

typedef void(*ResizeFunc)(uint32_t, uint32_t);
typedef void* WindowHandle;

class GameWindow {
#ifdef HANGAR_WINDOWS
	friend LRESULT MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
private:
	std::string title;
	uint32_t width, height;
	bool isRunning, isResizable;
	ResizeFunc resize;

	class Impl;
	Impl* windowImpl;
public:
	GameWindow(std::string title, uint32_t width, uint32_t height, bool isResizable);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;

	void Open();
	void Close();
	void Poll();
	void SetTitle(std::string newTitle);
	void SetSize(uint32_t width, uint32_t height);
	void SetReizeFunction(ResizeFunc func);
	WindowHandle GetHandle();

	bool IsRunning() const;
	bool IsFocus() const;
	inline bool IsResizable() { return isResizable; }
	inline std::string GetTitle() const { return title; }
	inline const uint32_t GetWidth() const { return width; }
	inline const uint32_t GetHeight() const { return height; }
};

#endif