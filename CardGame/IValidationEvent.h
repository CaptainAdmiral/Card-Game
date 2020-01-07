#pragma once

class IValidationEvent {
public:
	bool isValid;

	void setValid(bool valid) {
		isValid = valid;
	}
};