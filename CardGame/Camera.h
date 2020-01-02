#pragma once
#include "Settings.h"

namespace Camera {
	static unsigned int WIDTH = Settings::General::DEFAULT_WIDTH;
	static unsigned int HEIGHT = Settings::General::DEFAULT_HEIGHT;
	static int CAMERA_X = 0;
	static int CAMERA_Y = 0;
	static float ZOOM = 1;

	//Calculates and returns the camera translated x position for rendering
	float SCREEN_X(float x);
	//Calculates and returns the camera translated y position for rendering
	float SCREEN_Y(float y);
};

