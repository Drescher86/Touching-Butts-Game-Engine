#include "InputEventData.h"


InputEventData::InputEventData(Uint32 type, SDL_Keycode key)
	:BaseEventData("input")
{
	m_key = key;
	m_type = type;
}

SDL_Keycode InputEventData::getKeyCode()
{
	return m_key;
}

Uint32 InputEventData::getEventType()
{
	return m_type;
}
