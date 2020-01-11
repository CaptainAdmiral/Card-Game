#pragma once

class IValidationEvent {
public:
	bool isValid = true;

	void validate() {
		isValid = true;
	}

	void invalidate() {
		isValid = false;
	}
};