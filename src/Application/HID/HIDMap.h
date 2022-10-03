#pragma once
#include <vector>

#include "Application/Event/KeyboardEvent.h"
#include "Application/Event/MouseEvent.h"

const std::vector<KeyboardKey> KeyboardMap
{
	KeyboardKey::w, KeyboardKey::a, KeyboardKey::s, KeyboardKey::d,
	KeyboardKey::escape, KeyboardKey::space,
	KeyboardKey::leftShift,	KeyboardKey::rightShift, KeyboardKey::leftCtrl, KeyboardKey::rightCtrl
};

const std::vector<MouseButton> MouseMap
{
	MouseButton::left, MouseButton::right
};