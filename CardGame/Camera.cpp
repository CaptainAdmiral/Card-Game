#include "Camera.h"

float Camera::SCREEN_X(float x) {
	return x*ZOOM + CAMERA_X;
}

float Camera::SCREEN_Y(float y) {
	return y*ZOOM + CAMERA_Y;
}