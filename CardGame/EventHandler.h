#pragma once
#include <vector>
#include <memory>
#include <map>
#include "Event.h"
#include "IEventListener.h"

namespace EventHandler {
	namespace {
		static std::vector<IEventListener*>  observers;
		static std::map<const char*, std::unique_ptr<std::vector<IEventListener*>>> specificObservers;
	}

	void subscribe(IEventListener *listener);
	void unsubscribe(IEventListener *listener);

	void subscribeEvent(const char*, IEventListener *listener);
	void unsubscribeEvent(const char*, IEventListener *listener);

	void postEvent(Event &e);
};

