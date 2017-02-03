#include "EventSystem.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class IEventListener;

void EventSystem::fireEvent(BaseEventData eventData)
{
	initCheck();
	auto f = m_listenerMap.find(eventData.getEventType());
	if (f != m_listenerMap.end()) {
		std::vector<std::shared_ptr<IEventListener>>::iterator it = f->second.begin();
		for (; it != f->second.end(); it++) {
			it->get()->onEvent(eventData);
		}
	}
}

void EventSystem::listenToEventType(std::shared_ptr<IEventListener> listener, std::string eventType)
{
	std::transform(eventType.begin(), eventType.end(), eventType.begin(), ::tolower);
	initCheck();
	auto f = m_listenerMap.find(eventType);
	if (f != m_listenerMap.end()) {
		f->second.push_back(listener);
	}
	else
	{
		std::vector<std::shared_ptr<IEventListener>> list;
		list.push_back(listener);
		m_listenerMap.insert(std::make_pair(eventType, list));
	}
}

bool EventSystem::init()
{
	EngineSystem::init();
	initCheck();
	return true;
}

void EventSystem::shutdown()
{
	EngineSystem::shutdown();
}

EventSystem::EventSystem()
{
	//Do nothing
}

EventSystem::~EventSystem()
{
	//Do nothing
}
