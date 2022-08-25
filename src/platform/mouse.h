#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
private:
	class Impl;
	Impl* mouse_impl;
public:
	static Mouse*& get();
	static void initialize();
	static void deinitialize();

	Mouse();
	~Mouse();

	void process(MessagePacket packet);
	int get_x() const;
	int get_y() const;
	bool is_left_down() const;
	bool is_middle_down() const;
	bool is_right_down() const;
	void show();
	void hide();
};

#endif