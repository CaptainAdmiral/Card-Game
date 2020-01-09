#pragma once

typedef const char* EventType;

class Event {
public:
	static constexpr EventType TYPE = "";

	Event() {}
	~Event() {}

	virtual EventType getType() {
		return TYPE;
	}
};

