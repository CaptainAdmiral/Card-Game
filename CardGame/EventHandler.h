#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include "Event.h"
#include "IEventListener.h"

template<unsigned int T = 0>
class EventHandler final {
public:
	EventHandler() {}
	~EventHandler() {}

	static std::vector<IEventListener*> observers;

	static void subscribe(IEventListener *listener) {
		observers.push_back(listener);
	}
	static void unsubscribe(IEventListener *listener) {
		observers.erase(std::remove(observers.begin(), observers.end(), listener), observers.end());
	}
	static void postEvent(Event &e) {
		assert(e.getType() != 0 && "Event type was 0 on post, event ID was not requested or returned from virtual getType()");
		
		if(T != 0) {
			EventHandler<0>::postEvent(e);
		}

		for(IEventListener *observer : observers) {
			observer->notify(e);
		}
	}
};

