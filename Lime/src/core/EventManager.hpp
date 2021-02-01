/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManager.hpp
Purpose: Event Management
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

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

	void removeListener(EventID eventId, std::function<void(Event&)> const& listener) {
		listeners[eventId].remove(listener);
	}

	void sendEvent(Event& event){
		EventID type = event.getType();
		if (listeners[type].size() > 0) {
			for (auto const& listener : listeners[type]) {
				listener(event);
			}
		}
	}

	void sendEvent(EventID eventId){
		Event event(eventId);
		if (listeners[eventId].size() > 0) {
			for (auto const& listener : listeners[eventId]) {
				listener(event);
			}
		}
	}

	void sendTimedEvent(Event& event, long long ms) {
		auto now = std::chrono::steady_clock::now();
		auto futuretime = now + std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(ms));
		event.setParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_START, now);
		event.setParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_EXEC, futuretime);
		timequeue.push(event);
	}

	void update() {
		if (!timequeue.empty()) {
			Event top = timequeue.top();
			auto futuretime = top.getParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_EXEC);
			if (std::chrono::steady_clock::now() >= futuretime) {
				for (auto const& listener : listeners[EventID::E_TIMED_EVENT]) {
					listener(top);
					Event edebug(EventID::E_GRAPHICS_DEBUG_TOGGLE);
					sendEvent(edebug);
				}
				timequeue.pop();
			}
		}
	}

	void clear() {
		listeners.clear();
		while (timequeue.size() > 0) {
			timequeue.pop();
		}
	}

	// overloading equals operator 
	friend bool operator==(const std::function<void(Event&)>& a, const std::function<void(Event&)>& b) {
		return a.target<void(Event&)>() == b.target<void(Event&)>();
	}

	// overloading less than operator 
	friend bool operator<(const std::function<void(Event&)>& a, const std::function<void(Event&)>& b) {
		return a.target<void(Event&)>() < b.target<void(Event&)>();
	}

private:
	std::unordered_map < EventID, std::list < std::function<void(Event&)>>> listeners;

	struct Comp2 {
		bool operator()(Event& e1, Event& e2) const {
			auto e1_futuretime = e1.getParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_EXEC);
			auto e2_futuretime = e2.getParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_EXEC);
			return e1_futuretime > e2_futuretime;
		}
	};
	std::priority_queue<Event, std::vector<Event>, Comp2> timequeue;
};

#endif
