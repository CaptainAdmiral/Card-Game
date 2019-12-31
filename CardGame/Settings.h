#pragma once

struct SettingsWrapper {
	SettingsWrapper() {}
	~SettingsWrapper() {}

	const unsigned int DEFAULT_HEIGHT = 800;
	const unsigned int DEFAULT_WIDTH = 500;
};

class Settings {
public:
	static SettingsWrapper getSettings();
	Settings();
	virtual ~Settings();
};