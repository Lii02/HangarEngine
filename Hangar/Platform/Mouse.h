#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
private:
	class Impl;
	Impl* mouseImpl;
public:
	static Mouse*& Get();
	static void Initialize();
	static void DeInitialize();

	Mouse();
	~Mouse();

	void Process(MessagePacket packet);
	int GetX() const;
	int GetY() const;
	bool IsLeftDown() const;
	bool IsMiddleDown() const;
	bool IsRightDown() const;
	void ShowMouseCursor();
	void HideMouseCursor();
};

#endif