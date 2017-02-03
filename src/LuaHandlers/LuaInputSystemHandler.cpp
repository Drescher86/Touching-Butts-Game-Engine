#include "LuaInputSystemHandler.h"

std::map<std::string, KeyCode> LuaInputSystemHandler::m_stringToKeyMap;

void LuaInputSystemHandler::init() {
	m_stringToKeyMap.insert(pair<string, KeyCode>("a", KeyCode::A));
	m_stringToKeyMap.insert(pair<string, KeyCode>("b", KeyCode::B));
	m_stringToKeyMap.insert(pair<string, KeyCode>("c", KeyCode::C));
	m_stringToKeyMap.insert(pair<string, KeyCode>("d", KeyCode::D));
	m_stringToKeyMap.insert(pair<string, KeyCode>("e", KeyCode::E));
	m_stringToKeyMap.insert(pair<string, KeyCode>("f", KeyCode::F));
	m_stringToKeyMap.insert(pair<string, KeyCode>("g", KeyCode::G));
	m_stringToKeyMap.insert(pair<string, KeyCode>("h", KeyCode::H));
	m_stringToKeyMap.insert(pair<string, KeyCode>("i", KeyCode::I));
	m_stringToKeyMap.insert(pair<string, KeyCode>("j", KeyCode::J));
	m_stringToKeyMap.insert(pair<string, KeyCode>("k", KeyCode::K));
	m_stringToKeyMap.insert(pair<string, KeyCode>("l", KeyCode::L));
	m_stringToKeyMap.insert(pair<string, KeyCode>("m", KeyCode::M));
	m_stringToKeyMap.insert(pair<string, KeyCode>("n", KeyCode::N));
	m_stringToKeyMap.insert(pair<string, KeyCode>("o", KeyCode::O));
	m_stringToKeyMap.insert(pair<string, KeyCode>("p", KeyCode::P));
	m_stringToKeyMap.insert(pair<string, KeyCode>("q", KeyCode::Q));
	m_stringToKeyMap.insert(pair<string, KeyCode>("r", KeyCode::R));
	m_stringToKeyMap.insert(pair<string, KeyCode>("s", KeyCode::S));
	m_stringToKeyMap.insert(pair<string, KeyCode>("t", KeyCode::T));
	m_stringToKeyMap.insert(pair<string, KeyCode>("u", KeyCode::U));
	m_stringToKeyMap.insert(pair<string, KeyCode>("v", KeyCode::V));
	m_stringToKeyMap.insert(pair<string, KeyCode>("x", KeyCode::X));
	m_stringToKeyMap.insert(pair<string, KeyCode>("y", KeyCode::Y));
	m_stringToKeyMap.insert(pair<string, KeyCode>("z", KeyCode::Z));
	m_stringToKeyMap.insert(pair<string, KeyCode>("w", KeyCode::W));
	m_stringToKeyMap.insert(pair<string, KeyCode>("alt", KeyCode::ALT));
	m_stringToKeyMap.insert(pair<string, KeyCode>("alt_gr", KeyCode::ALT_GR));
	m_stringToKeyMap.insert(pair<string, KeyCode>("left_shift", KeyCode::LEFT_SHIFT));
	m_stringToKeyMap.insert(pair<string, KeyCode>("right_shift", KeyCode::RIGHT_SHIFT));
	m_stringToKeyMap.insert(pair<string, KeyCode>("left_arrow", KeyCode::LEFT_ARROW));
	m_stringToKeyMap.insert(pair<string, KeyCode>("right_arrow", KeyCode::RIGHT_ARROW));
	m_stringToKeyMap.insert(pair<string, KeyCode>("up_arrow", KeyCode::UP_ARROW));
	m_stringToKeyMap.insert(pair<string, KeyCode>("down_arrow", KeyCode::DOWN_ARROW));
	m_stringToKeyMap.insert(pair<string, KeyCode>("tab", KeyCode::TAB));
	m_stringToKeyMap.insert(pair<string, KeyCode>("space", KeyCode::SPACE));
	m_stringToKeyMap.insert(pair<string, KeyCode>("enter", KeyCode::ENTER));
	m_stringToKeyMap.insert(pair<string, KeyCode>("1", KeyCode::ONE));
	m_stringToKeyMap.insert(pair<string, KeyCode>("2", KeyCode::TWO));
	m_stringToKeyMap.insert(pair<string, KeyCode>("3", KeyCode::THREE));
	m_stringToKeyMap.insert(pair<string, KeyCode>("4", KeyCode::FOUR));
	m_stringToKeyMap.insert(pair<string, KeyCode>("5", KeyCode::FIVE));
	m_stringToKeyMap.insert(pair<string, KeyCode>("6", KeyCode::SIX));
	m_stringToKeyMap.insert(pair<string, KeyCode>("7", KeyCode::SEVEN));
	m_stringToKeyMap.insert(pair<string, KeyCode>("8", KeyCode::EIGHT));
	m_stringToKeyMap.insert(pair<string, KeyCode>("9", KeyCode::NINE));
	m_stringToKeyMap.insert(pair<string, KeyCode>("0", KeyCode::ZERO));
	m_stringToKeyMap.insert(pair<string, KeyCode>("escape", KeyCode::ESCAPE));
	m_stringToKeyMap.insert(pair<string, KeyCode>("left_control", KeyCode::LEFT_CONTROL));
	m_stringToKeyMap.insert(pair<string, KeyCode>("right_control", KeyCode::RIGHT_CONTROL));
	m_stringToKeyMap.insert(pair<string, KeyCode>("left_mouse_button", KeyCode::LEFT_MOUSE_BUTTON));
	m_stringToKeyMap.insert(pair<string, KeyCode>("right_mouse_button", KeyCode::RIGHT_MOUSE_BUTTON));
	m_stringToKeyMap.insert(pair<string, KeyCode>("mouse_wheel_pull", KeyCode::MOUSE_WHEEL_PULL));
	m_stringToKeyMap.insert(pair<string, KeyCode>("mouse_wheel_push", KeyCode::MOUSE_WHEEL_PUSH));
	m_stringToKeyMap.insert(pair<string, KeyCode>("quit", KeyCode::QUIT));
	isInitialized = true;

}

std::string LuaInputSystemHandler::toLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

bool LuaInputSystemHandler::getKeyDown(std::string keyCode)
{
	if (!isInitialized)
		init();
	keyCode = toLower(keyCode);
	auto k = m_stringToKeyMap.find(keyCode);
	assert((k != m_stringToKeyMap.end()) && ("Keycode not found"));
	if (k != m_stringToKeyMap.end()) {
		return g_inputSystem->getKeyDown(k->second);
	}
	return false;
}

bool LuaInputSystemHandler::getKeyUp(std::string keyCode)
{
	if (!isInitialized)
		init();
	keyCode = toLower(keyCode);
	auto k = m_stringToKeyMap.find(keyCode);
	assert((k != m_stringToKeyMap.end()) && ("Keycode not found"));
	if (k != m_stringToKeyMap.end()) {
		return g_inputSystem->getKeyUp(k->second);
	}
	return false;
}

bool LuaInputSystemHandler::getKeyPressed(std::string keyCode)
{
	if (!isInitialized)
		init();
	keyCode = toLower(keyCode);
	auto k = m_stringToKeyMap.find(keyCode);
	assert((k != m_stringToKeyMap.end()) && ("Keycode not found"));
	if (k != m_stringToKeyMap.end()) {
		return g_inputSystem->getKeyPressed(k->second);
	}
	return false;
}

bool LuaInputSystemHandler::getKeyReleased(std::string keyCode)
{
	if (!isInitialized)
		init();
	keyCode = toLower(keyCode);
	auto k = m_stringToKeyMap.find(keyCode);
	assert((k != m_stringToKeyMap.end()) && ("Keycode not found"));
	if (k != m_stringToKeyMap.end()) {
		return g_inputSystem->getKeyReleased(k->second);
	}
	return false;
}

float LuaInputSystemHandler::getWheelY()
{
	return g_inputSystem->getWheelY();
}

Vector2 LuaInputSystemHandler::getMousePosition()
{
	auto vec = g_inputSystem->getMousePosition();
	return Vector2(vec.x, vec.y);
}
