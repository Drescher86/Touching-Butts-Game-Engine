#pragma once
#include <vector>
#include <memory>
#include "EngineSystem.h"
#include "SDL.h"
#include "glm/glm.hpp"
#include <map>

using namespace std;
/*! KeyCode enum class representing all available key events from the game. */
enum KeyCode {
	MOUSE_WHEEL_PUSH,
	MOUSE_WHEEL_PULL,
	RIGHT_MOUSE_BUTTON,
	LEFT_MOUSE_BUTTON,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	X,
	Y,
	Z,
	W,
	LEFT_ARROW,
	RIGHT_ARROW,
	UP_ARROW,
	DOWN_ARROW,
	SPACE,
	ENTER,
	ESCAPE,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	ZERO,
	LEFT_CONTROL,
	RIGHT_CONTROL,
	ALT,
	ALT_GR,
	LEFT_SHIFT,
	RIGHT_SHIFT,
	TAB,
	QUIT
};
/**
Input system responsible for handling input.
*/
class InputSystem : public EngineSystem {
public:
	/**
	Get whether specific key is down.
	*/
	bool getKeyDown(KeyCode keyCode/**KeyCode of specific key.*/);
	/**
	Get whether specific key is up.
	*/
	bool getKeyUp(KeyCode keyCode/**KeyCode of specific key.*/);
	/**
	Get whether specific key has been pressed. Only true once per click.
	*/
	bool getKeyPressed(KeyCode keyCode/**KeyCode of specific key.*/);
	/**
	Get whether specific key has been released. Only true once after a click.
	*/
	bool getKeyReleased(KeyCode keyCode/**KeyCode of specfic key.*/);
	/**
	Get scroll of mouse wheel. Positive away from user, negative toward user.
	*/
	float getWheelY();
	/**
	Get current mouse position in 2D world coordinates.
	*/
	glm::vec2 getMousePosition();

	InputSystem();
	~InputSystem();
protected:
	virtual bool init() override;
	virtual void shutdown() override;
	void handleInput();
	friend class TouchingButts;
private:
	void setKey(SDL_Keycode code, bool down);
	void setKey(Uint8 button, bool down);

	glm::vec2 m_mousePosition;
	
	std::map<KeyCode, bool> m_keyMap;
	std::map<KeyCode, bool> m_keyMapLastFrame;


	float m_wheelY;
};