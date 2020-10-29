#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Pch.hpp"
#include "core/Event.hpp"

class EventManager
{
public:
	void addListener(EventID eventId, std::function<void(Event&)> const& listener){
		listeners[eventId].push_back(listener);
	}

	void sendEvent(Event& event){
		uint32_t type = event.getType();
		for (auto const& listener : listeners[type]){
			listener(event);
		}
	}

	void sendEvent(EventID eventId){
		Event event(eventId);
		for (auto const& listener : listeners[eventId]){
			listener(event);
		}
	}

private:
	std::unordered_map<EventID, std::list<std::function<void(Event&)>>> listeners;
};

#endif
