#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
private:
	class Impl;
	Impl* keyboardImplementation;
public:
	static Keyboard& Get();

	Keyboard();
	~Keyboard();

	void Process(MessagePacket packet);
	bool GetKey(uint8_t code) const;
};

#endif