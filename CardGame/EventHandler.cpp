#include "EventHandler.h"
#include <algorithm>
#include <assert.h>

void EventHandler::subscribe(IEventListener *listener) {
	observers.push_back(listener);
}

void EventHandler::unsubscribe(IEventListener *listener) {
	observers.erase(std::remove(observers.begin(), observers.end(), listener), observers.end());
}

void EventHandler::subscribeEvent(const char *eventName, IEventListener *listener) {
	if(!specificObservers[eventName]) {
		specificObservers[eventName] = std::make_unique<std::vector<IEventListener*>>();
	}
	specificObservers[eventName]->push_back(listener);
}

void EventHandler::unsubscribeEvent(const char *eventName, IEventListener *listener) {
	specificObservers[eventName]->erase(std::remove(observers.begin(), observers.end(), listener), observers.end());
}

void EventHandler::postEvent(Event &e) {
	assert(e.getType() != Event::TYPE && "Event type was null char on post, virtual type() was not overrided for event");

	for(IEventListener *observer : observers) {
		observer->notify(e);
	}

	if(specificObservers[e.getType()]) {
		for(IEventListener *observer : *specificObservers[e.getType()]) {
			observer->notify(e);
		}
	}
}
