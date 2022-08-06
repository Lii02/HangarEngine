#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

class GameWindow {
private:
	std::string title;
	uint32_t width, height;
	bool isRunning, isResizable;

	class Impl;
	Impl* windowImplementation;
public:
	GameWindow(std::string title, uint32_t width, uint32_t height, bool isResizable);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;

	void Open();
	void Close();
	void Poll();
	void SetTitle(std::string newTitle);
	void SetSize(uint32_t width, uint32_t height);
	std::vector<const char*> GetVulkanInstExtensions() const;
	VkSurfaceKHR CreateVulkanSurface(VkInstance& instance);

	bool IsRunning() const;
	inline bool IsResizable() { return isResizable; }
	inline std::string GetTitle() const { return title; }
	inline const uint32_t GetWidth() const { return width; }
	inline const uint32_t GetHeight() const { return height; }
};

#endif