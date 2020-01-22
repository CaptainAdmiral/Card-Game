#pragma once
#include <assert.h>

typedef const char* EventType;

class Event {
public:
	static constexpr EventType TYPE = "";

	Event() {}
	virtual ~Event() {}

	virtual EventType getType() {
		return TYPE;
	}

	virtual bool isCanceleable() {
		return false;
	}

	bool isCanceled() {
		return canceled;
	}

	void setCanceled() {
		assert(isCanceleable());
		canceled = true;
	}

private:
	bool canceled = false;
};

