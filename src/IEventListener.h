#pragma once
#include "BaseEventData.h"
/**
Interface for subscribing to events.
*/
class IEventListener {
public:
	/**
	On event.
	*/
	virtual void onEvent(BaseEventData eventData) = 0;
};
