#pragma once

struct SettingsWrapper {
	SettingsWrapper() {}
	~SettingsWrapper() {}

	const unsigned int DEFAULT_HEIGHT = 500;
	const unsigned int DEFAULT_WIDTH = 275;
};

class Settings {
public:
	static SettingsWrapper getSettings();
	Settings();
	virtual ~Settings();
};