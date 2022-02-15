#include"Keyboard.hpp"

std::unordered_map<Keyboard::Key, bool> Keyboard::keyPressMap;

bool Keyboard::getKeyPress(const Key& key)
{
	return keyPressMap[key];
}

void Keyboard::ini()
{
	keyPressMap.insert(std::pair<Key, bool>(Space, false));
	keyPressMap.insert(std::pair<Key, bool>(Apostrophe, false));
	keyPressMap.insert(std::pair<Key, bool>(Comma, false));
	keyPressMap.insert(std::pair<Key, bool>(Minus, false));
	keyPressMap.insert(std::pair<Key, bool>(Period, false));
	keyPressMap.insert(std::pair<Key, bool>(Slash, false));
	keyPressMap.insert(std::pair<Key, bool>(Num0, false));
	keyPressMap.insert(std::pair<Key, bool>(Num1, false));
	keyPressMap.insert(std::pair<Key, bool>(Num2, false));
	keyPressMap.insert(std::pair<Key, bool>(Num3, false));
	keyPressMap.insert(std::pair<Key, bool>(Num4, false));
	keyPressMap.insert(std::pair<Key, bool>(Num5, false));
	keyPressMap.insert(std::pair<Key, bool>(Num6, false));
	keyPressMap.insert(std::pair<Key, bool>(Num7, false));
	keyPressMap.insert(std::pair<Key, bool>(Num8, false));
	keyPressMap.insert(std::pair<Key, bool>(Num9, false));
	keyPressMap.insert(std::pair<Key, bool>(Semicolon, false));
	keyPressMap.insert(std::pair<Key, bool>(Equal, false));
	keyPressMap.insert(std::pair<Key, bool>(A, false));
	keyPressMap.insert(std::pair<Key, bool>(B, false));
	keyPressMap.insert(std::pair<Key, bool>(C, false));
	keyPressMap.insert(std::pair<Key, bool>(D, false));
	keyPressMap.insert(std::pair<Key, bool>(E, false));
	keyPressMap.insert(std::pair<Key, bool>(F, false));
	keyPressMap.insert(std::pair<Key, bool>(G, false));
	keyPressMap.insert(std::pair<Key, bool>(H, false));
	keyPressMap.insert(std::pair<Key, bool>(I, false));
	keyPressMap.insert(std::pair<Key, bool>(J, false));
	keyPressMap.insert(std::pair<Key, bool>(K, false));
	keyPressMap.insert(std::pair<Key, bool>(L, false));
	keyPressMap.insert(std::pair<Key, bool>(M, false));
	keyPressMap.insert(std::pair<Key, bool>(N, false));
	keyPressMap.insert(std::pair<Key, bool>(O, false));
	keyPressMap.insert(std::pair<Key, bool>(P, false));
	keyPressMap.insert(std::pair<Key, bool>(Q, false));
	keyPressMap.insert(std::pair<Key, bool>(R, false));
	keyPressMap.insert(std::pair<Key, bool>(S, false));
	keyPressMap.insert(std::pair<Key, bool>(T, false));
	keyPressMap.insert(std::pair<Key, bool>(U, false));
	keyPressMap.insert(std::pair<Key, bool>(V, false));
	keyPressMap.insert(std::pair<Key, bool>(W, false));
	keyPressMap.insert(std::pair<Key, bool>(X, false));
	keyPressMap.insert(std::pair<Key, bool>(Y, false));
	keyPressMap.insert(std::pair<Key, bool>(Z, false));
	keyPressMap.insert(std::pair<Key, bool>(Left_Bracket, false));
	keyPressMap.insert(std::pair<Key, bool>(Backslash, false));
	keyPressMap.insert(std::pair<Key, bool>(Right_Bracket, false));
	keyPressMap.insert(std::pair<Key, bool>(Grave_Accent, false));
	keyPressMap.insert(std::pair<Key, bool>(Escape, false));
	keyPressMap.insert(std::pair<Key, bool>(Enter, false));
	keyPressMap.insert(std::pair<Key, bool>(Tab, false));
	keyPressMap.insert(std::pair<Key, bool>(Backspace, false));
	keyPressMap.insert(std::pair<Key, bool>(Insert, false));
	keyPressMap.insert(std::pair<Key, bool>(Delete, false));
	keyPressMap.insert(std::pair<Key, bool>(Right, false));
	keyPressMap.insert(std::pair<Key, bool>(Left, false));
	keyPressMap.insert(std::pair<Key, bool>(Down, false));
	keyPressMap.insert(std::pair<Key, bool>(Up, false));
	keyPressMap.insert(std::pair<Key, bool>(Page_Up, false));
	keyPressMap.insert(std::pair<Key, bool>(PAGE_Down, false));
	keyPressMap.insert(std::pair<Key, bool>(Home, false));
	keyPressMap.insert(std::pair<Key, bool>(End, false));
	keyPressMap.insert(std::pair<Key, bool>(Caps_Lock, false));
	keyPressMap.insert(std::pair<Key, bool>(Scroll_Lock, false));
	keyPressMap.insert(std::pair<Key, bool>(Num_Lock, false));
	keyPressMap.insert(std::pair<Key, bool>(Print_Screen, false));
	keyPressMap.insert(std::pair<Key, bool>(Pause, false));
	keyPressMap.insert(std::pair<Key, bool>(F1, false));
	keyPressMap.insert(std::pair<Key, bool>(F2, false));
	keyPressMap.insert(std::pair<Key, bool>(F3, false));
	keyPressMap.insert(std::pair<Key, bool>(F4, false));
	keyPressMap.insert(std::pair<Key, bool>(F5, false));
	keyPressMap.insert(std::pair<Key, bool>(F6, false));
	keyPressMap.insert(std::pair<Key, bool>(F7, false));
	keyPressMap.insert(std::pair<Key, bool>(F8, false));
	keyPressMap.insert(std::pair<Key, bool>(F9, false));
	keyPressMap.insert(std::pair<Key, bool>(F10, false));
	keyPressMap.insert(std::pair<Key, bool>(F11, false));
	keyPressMap.insert(std::pair<Key, bool>(F12, false));
	keyPressMap.insert(std::pair<Key, bool>(F13, false));
	keyPressMap.insert(std::pair<Key, bool>(F14, false));
	keyPressMap.insert(std::pair<Key, bool>(F15, false));
	keyPressMap.insert(std::pair<Key, bool>(F16, false));
	keyPressMap.insert(std::pair<Key, bool>(F17, false));
	keyPressMap.insert(std::pair<Key, bool>(F18, false));
	keyPressMap.insert(std::pair<Key, bool>(F19, false));
	keyPressMap.insert(std::pair<Key, bool>(F20, false));
	keyPressMap.insert(std::pair<Key, bool>(F21, false));
	keyPressMap.insert(std::pair<Key, bool>(F22, false));
	keyPressMap.insert(std::pair<Key, bool>(F23, false));
	keyPressMap.insert(std::pair<Key, bool>(F24, false));
	keyPressMap.insert(std::pair<Key, bool>(F25, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad0, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad1, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad2, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad3, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad4, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad5, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad6, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad7, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad8, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad9, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Decimal, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Divide, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Multiply, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Subtract, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Add, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Enter, false));
	keyPressMap.insert(std::pair<Key, bool>(Numpad_Equal, false));
	keyPressMap.insert(std::pair<Key, bool>(Left_Shift, false));
	keyPressMap.insert(std::pair<Key, bool>(Left_Control, false));
	keyPressMap.insert(std::pair<Key, bool>(Left_Alt, false));
	keyPressMap.insert(std::pair<Key, bool>(Left_Super, false));
	keyPressMap.insert(std::pair<Key, bool>(Right_Shift, false));
	keyPressMap.insert(std::pair<Key, bool>(Right_Control, false));
	keyPressMap.insert(std::pair<Key, bool>(Right_Alt, false));
	keyPressMap.insert(std::pair<Key, bool>(Right_Super, false));
	keyPressMap.insert(std::pair<Key, bool>(Menu, false));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Keyboard::keyPressMap[(Keyboard::Key)key] = true;
		break;
	case GLFW_RELEASE:
		Keyboard::keyPressMap[(Keyboard::Key)key] = false;
		break;
	default:
		break;
	}
}