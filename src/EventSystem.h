#pragma once
#include "EngineSystem.h"
#include <map>
#include <vector>
#include "IEventListener.h"
#include "BaseEventData.h"
#include <memory>
/**
Event system responsible for firing events to every subscriber.
*/
class EventSystem : public EngineSystem
{
public:
	/**
	Fire an sub type BaseEvenData event.
	*/
	void fireEvent(BaseEventData eventData/**Event type fired.*/);
	/**
	Subscribe to event type.
	*/
	void listenToEventType(std::shared_ptr<IEventListener> listener/**Shared pointer to listener.*/, std::string eventType/**Type of event subscribed to.*/);

	virtual bool init() override;
	virtual void shutdown() override;
	EventSystem();
	~EventSystem();

private:
	std::map<std::string, std::vector<std::shared_ptr<IEventListener>>> m_listenerMap;
};