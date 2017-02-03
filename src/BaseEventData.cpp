#include <algorithm>
#include "BaseEventData.h"

using namespace std;

BaseEventData::BaseEventData(string eventType) {

	std::transform(eventType.begin(), eventType.end(), eventType.begin(), ::tolower);
	m_eventType = eventType;
}

BaseEventData::BaseEventData(GameObject * gameObject, std::string eventType)
{
	std::transform(eventType.begin(), eventType.end(), eventType.begin(), ::tolower);
	m_eventType = eventType;
	m_gameObject = gameObject;
}

std::string BaseEventData::getEventType()
{
	return m_eventType;
}

GameObject * BaseEventData::getGameObject()
{
	return m_gameObject;
}
