#include "InputSystem.h"
#include "TouchingButts.hpp"
#include "InputEventData.h"

bool InputSystem::init()
{
	EngineSystem::init();

	m_keyMap.insert(pair<KeyCode,bool>(KeyCode::A, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::B, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::C, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::D, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::E, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::F, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::G, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::H, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::I, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::J, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::K, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::L, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::M, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::N, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::O, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::P, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::Q, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::R, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::S, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::T, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::U, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::V, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::X, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::Y, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::Z, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::W, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::ALT, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::ALT_GR, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::ONE, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::TWO, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::THREE, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::FOUR, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::FIVE, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::SIX, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::SEVEN, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::EIGHT, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::NINE, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::ZERO, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::SPACE, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::ENTER, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::ESCAPE, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::LEFT_SHIFT, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::RIGHT_SHIFT, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::DOWN_ARROW, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::RIGHT_ARROW, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::LEFT_ARROW, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::UP_ARROW, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::TAB, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::LEFT_CONTROL, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::RIGHT_CONTROL, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::LEFT_MOUSE_BUTTON, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::RIGHT_MOUSE_BUTTON, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::MOUSE_WHEEL_PULL, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::MOUSE_WHEEL_PUSH, false));
	m_keyMap.insert(pair<KeyCode, bool>(KeyCode::QUIT, false));
	
	map<KeyCode, bool>::iterator it = m_keyMap.begin();
	for (; it != m_keyMap.end(); it++) {
		m_keyMapLastFrame.insert(pair<KeyCode, bool>(it->first, it->second));
	}
	

	initCheck();
	return true;
}

void InputSystem::shutdown()
{
	EngineSystem::shutdown();
}

void InputSystem::handleInput()
{
	bool mouseWheel = false;
	SDL_Event event;
	/* Poll for events */
	map<KeyCode, bool>::iterator it = m_keyMap.begin();
	for (; it != m_keyMap.end(); it++) {
		m_keyMapLastFrame.at(it->first) = it->second;
	}
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_keyMap.at(KeyCode::QUIT) = true;
				break;
			case SDL_KEYDOWN:
				setKey(event.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				setKey(event.key.keysym.sym, false);
				break;
			case SDL_MOUSEBUTTONUP:
				setKey(event.button.button, false);
				break;
			case SDL_MOUSEBUTTONDOWN:
				setKey(event.button.button, true);
				break;
			case SDL_MOUSEWHEEL:
				mouseWheel = true;
				m_wheelY = event.wheel.y;
				if (event.wheel.y > 0)
					m_keyMap.at(KeyCode::MOUSE_WHEEL_PULL) = true;
				else
					m_keyMap.at(KeyCode::MOUSE_WHEEL_PULL) = false;
				if (event.wheel.y < 0)
					m_keyMap.at(KeyCode::MOUSE_WHEEL_PUSH) = true;
				else
					m_keyMap.at(KeyCode::MOUSE_WHEEL_PUSH) = false;
			case SDL_MOUSEMOTION:
				m_mousePosition = glm::vec2(event.motion.x, g_windowSize.y()-event.motion.y);
				m_mousePosition -= glm::vec2(g_sceneSystem->getCameraPosition());
				break;
			default:
				break;
		}
	}
	if (!mouseWheel)
	{
		m_keyMap.at(KeyCode::MOUSE_WHEEL_PULL) = false;
		m_keyMap.at(KeyCode::MOUSE_WHEEL_PUSH) = false;
	}
}

bool InputSystem::getKeyDown(KeyCode keyCode)
{
	
	return m_keyMap.at(keyCode);
}

bool InputSystem::getKeyPressed(KeyCode keyCode) {
	return m_keyMap.at(keyCode) && !m_keyMapLastFrame.at(keyCode);
}

bool InputSystem::getKeyUp(KeyCode keyCode)
{
	return !m_keyMap.at(keyCode);
}

bool InputSystem::getKeyReleased(KeyCode keyCode) {
	return !m_keyMap.at(keyCode) && m_keyMapLastFrame.at(keyCode);
}

float InputSystem::getWheelY()
{
	return m_wheelY;
}

void InputSystem::setKey(SDL_Keycode code, bool down) {
	switch (code)
	{
		case SDLK_0:
			m_keyMap.at(KeyCode::ZERO) = down;
			break;
		case SDLK_1:
			m_keyMap.at(KeyCode::ONE) = down;
			break;
		case SDLK_2:
			m_keyMap.at(KeyCode::TWO) = down;
			break;
		case SDLK_3:
			m_keyMap.at(KeyCode::THREE) = down;
			break;
		case SDLK_4:
			m_keyMap.at(KeyCode::FOUR) = down;
			break;
		case SDLK_5:
			m_keyMap.at(KeyCode::FIVE) = down;
			break;
		case SDLK_6:
			m_keyMap.at(KeyCode::SIX) = down;
			break;
		case SDLK_7:
			m_keyMap.at(KeyCode::SEVEN) = down;
			break;
		case SDLK_8:
			m_keyMap.at(KeyCode::EIGHT) = down;
			break;
		case SDLK_9:
			m_keyMap.at(KeyCode::NINE) = down;
			break;
		case SDLK_a:
			m_keyMap.at(KeyCode::A) = down;
			break;
		case SDLK_b:
			m_keyMap.at(KeyCode::B) = down;
			break;
		case SDLK_c:
			m_keyMap.at(KeyCode::C) = down;
			break;
		case SDLK_d:
			m_keyMap.at(KeyCode::D) = down;
			break;
		case SDLK_e:
			m_keyMap.at(KeyCode::E) = down;
			break;
		case SDLK_f:
			m_keyMap.at(KeyCode::F) = down;
			break;
		case SDLK_g:
			m_keyMap.at(KeyCode::G) = down;
			break;
		case SDLK_h:
			m_keyMap.at(KeyCode::H) = down;
			break;
		case SDLK_i:
			m_keyMap.at(KeyCode::I) = down;
			break;
		case SDLK_j:
			m_keyMap.at(KeyCode::J) = down;
			break;
		case SDLK_k:
			m_keyMap.at(KeyCode::K) = down;
			break;
		case SDLK_l:
			m_keyMap.at(KeyCode::L) = down;
			break;
		case SDLK_m:
			m_keyMap.at(KeyCode::M) = down;
			break;
		case SDLK_n:
			m_keyMap.at(KeyCode::N) = down;
			break;
		case SDLK_o:
			m_keyMap.at(KeyCode::O) = down;
			break;
		case SDLK_p:
			m_keyMap.at(KeyCode::P) = down;
			break;
		case SDLK_q:
			m_keyMap.at(KeyCode::Q) = down;
			break;
		case SDLK_r:
			m_keyMap.at(KeyCode::R) = down;
			break;
		case SDLK_s:
			m_keyMap.at(KeyCode::S) = down;
			break;
		case SDLK_t:
			m_keyMap.at(KeyCode::T) = down;
			break;
		case SDLK_u:
			m_keyMap.at(KeyCode::U) = down;
			break;
		case SDLK_v:
			m_keyMap.at(KeyCode::V) = down;
			break;
		case SDLK_x:
			m_keyMap.at(KeyCode::X) = down;
			break;
		case SDLK_y:
			m_keyMap.at(KeyCode::Y) = down;
			break;
		case SDLK_z:
			m_keyMap.at(KeyCode::Z) = down;
			break;
		case SDLK_w:
			m_keyMap.at(KeyCode::W) = down;
			break;
		case SDLK_LEFT:
			m_keyMap.at(KeyCode::LEFT_ARROW) = down;
			break;
		case SDLK_RIGHT:
			m_keyMap.at(KeyCode::RIGHT_ARROW) = down;
			break;
		case SDLK_UP:
			m_keyMap.at(KeyCode::UP_ARROW) = down;
			break;
		case SDLK_DOWN:
			m_keyMap.at(KeyCode::DOWN_ARROW) = down;
			break;
		case SDLK_ESCAPE:
			m_keyMap.at(KeyCode::ESCAPE) = down;
			break;
		case SDLK_SPACE:
			m_keyMap.at(KeyCode::SPACE) = down;
			break;
		case SDLK_RETURN:
			m_keyMap.at(KeyCode::ENTER) = down;
			break;
		case SDLK_LCTRL:
			m_keyMap.at(KeyCode::LEFT_CONTROL) = down;
			break;
		case SDLK_RCTRL:
			m_keyMap.at(KeyCode::RIGHT_CONTROL) = down;
			break;
		case SDLK_LALT:
			m_keyMap.at(KeyCode::ALT) = down;
			break;
		case SDLK_RALT:
			m_keyMap.at(KeyCode::ALT_GR) = down;
			break;
		case SDLK_LSHIFT:
			m_keyMap.at(KeyCode::LEFT_SHIFT) = down;
			break;
		case SDLK_RSHIFT:
			m_keyMap.at(KeyCode::RIGHT_SHIFT) = down;
			break;
		case SDLK_TAB:
			m_keyMap.at(KeyCode::TAB) = down;
			break;
		default:
			break;
	}
}

void InputSystem::setKey(Uint8 button, bool down) {
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			m_keyMap.at(KeyCode::LEFT_MOUSE_BUTTON) = down;
			break;
		case SDL_BUTTON_RIGHT:
			m_keyMap.at(KeyCode::RIGHT_MOUSE_BUTTON) = down;
			break;
		default:
			break;

	}
}

glm::vec2 InputSystem::getMousePosition() {
	return m_mousePosition;
}

InputSystem::InputSystem()
{
	//do nothing!
}

InputSystem::~InputSystem()
{
	//Do nothing!
}
