#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef HANGAR_WINDOWS
enum KeyCode : uint8_t
{
	KEY_SPACE = VK_SPACE,
	KEY_ESCAPE = VK_ESCAPE,
	KEY_TILDA = '`',
	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',
	KEY_5 = '5',
	KEY_6 = '6',
	KEY_7 = '7',
	KEY_8 = '8',
	KEY_9 = '9',
	KEY_0 = '0',
	KEY_SUBTRACT = '-',
	KEY_ADD = '+',
	KEY_BACKSPACE = VK_BACK,
	KEY_TAB = VK_TAB,
	KEY_Q = 'Q',
	KEY_W = 'W',
	KEY_E = 'E',
	KEY_R = 'R',
	KEY_T = 'T',
	KEY_Y = 'Y',
	KEY_U = 'U',
	KEY_I = 'I',
	KEY_O = 'O',
	KEY_P = 'P',
	KEY_LBRACKET = '[',
	KEY_RBRACKET = ']',
	KEY_BACKSLASH = '\\',
	KEY_A = 'A',
	KEY_S = 'S',
	KEY_D = 'D',
	KEY_F = 'F',
	KEY_G = 'G',
	KEY_H = 'H',
	KEY_J = 'J',
	KEY_K = 'K',
	KEY_L = 'L',
	KEY_APOSTRAPHE = '\'',
	KEY_PERIOD = '.',
	KEY_RETURN = VK_RETURN,
	KEY_LSHIFT = VK_LSHIFT,
	KEY_Z = 'Z',
	KEY_X = 'X',
	KEY_C = 'C',
	KEY_V = 'V',
	KEY_B = 'B',
	KEY_N = 'N',
	KEY_M = 'M',
	KEY_COMMA = ',',
	KEY_SLASH = '/',
	KEY_RSHIFT = VK_RSHIFT,
	KEY_LCTRL = VK_LCONTROL,
	KEY_CAPSLOCK = VK_CAPITAL,
	KEY_LALT = VK_LMENU,
	KEY_RALT = VK_RMENU,
	KEY_RCTRL = VK_RCONTROL,
	KEY_UP = VK_UP,
	KEY_LEFT = VK_LEFT,
	KEY_DOWN = VK_DOWN,
	KEY_RIGHT = VK_RIGHT,
	KEY_INSERT = VK_INSERT,
	KEY_DELETE = VK_DELETE,
	KEY_HOME = VK_HOME,
	KEY_END = VK_END,
	KEY_NUMLOCK = VK_NUMLOCK,
	KEY_NUMPAD_DIVIDE = VK_DIVIDE,
	KEY_NUMPAD_MULTIPLY = VK_MULTIPLY,
	KEY_NUMPAD_SUBTRACT = VK_SUBTRACT,
	KEY_NUMPAD_DECIMAL = VK_DECIMAL,
	KEY_NUMPAD_ADD = VK_ADD,
	KEY_NUMPAD0 = VK_NUMPAD0,
	KEY_NUMPAD1 = VK_NUMPAD1,
	KEY_NUMPAD2 = VK_NUMPAD2,
	KEY_NUMPAD3 = VK_NUMPAD3,
	KEY_NUMPAD4 = VK_NUMPAD4,
	KEY_NUMPAD5 = VK_NUMPAD5,
	KEY_NUMPAD6 = VK_NUMPAD6,
	KEY_NUMPAD7 = VK_NUMPAD7,
	KEY_NUMPAD8 = VK_NUMPAD8,
	KEY_NUMPAD9 = VK_NUMPAD9,
	KEY_PRINTSCREEN = VK_SNAPSHOT,
	KEY_SCROLLLOCK = VK_SCROLL,
	KEY_HELP = VK_HELP,
	KEY_LWIN = VK_LWIN,
	KEY_RWIN = VK_RWIN,
	KEY_SEPERATOR = VK_SEPARATOR,
	KEY_F1 = VK_F1,
	KEY_F2 = VK_F2,
	KEY_F3 = VK_F3,
	KEY_F4 = VK_F4,
	KEY_F5 = VK_F5,
	KEY_F6 = VK_F6,
	KEY_F7 = VK_F7,
	KEY_F8 = VK_F8,
	KEY_F9 = VK_F9,
	KEY_F10 = VK_F10,
	KEY_F11 = VK_F11,
	KEY_F12 = VK_F12,
};
#endif

class Keyboard {
private:
	class Impl;
	Impl* keyboard_impl;
public:
	static Keyboard*& get();
	static void initialize();
	static void deinitialize();

	Keyboard();
	~Keyboard();

	void process(MessagePacket packet);
	bool get_key(KeyCode code) const;
};

#endif