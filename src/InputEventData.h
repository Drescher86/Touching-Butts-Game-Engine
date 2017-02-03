#pragma once
#include "SDL.h"
#include "BaseEventData.h"
#include <string>

class InputEventData : public BaseEventData {
public:
	InputEventData(Uint32 type, SDL_Keycode key);
	SDL_Keycode getKeyCode();
	Uint32 getEventType();
private:
	SDL_Keycode m_key;
	Uint32 m_type;
};