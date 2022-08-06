#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
private:
	class Impl;
	Impl* mouseImplementation;
public:
	static Mouse& Get();

	Mouse();
	~Mouse();

	void Process(MessagePacket packet);
	int GetX() const;
	int GetY() const;
	bool IsLeftDown() const;
	bool IsMiddleDown() const;
	bool IsRightDown() const;
};

#endif