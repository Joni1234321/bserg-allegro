#pragma once

#include "allegro5/keycodes.h"

#include "camera.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2

#define KEYCODE_DOWN 1	
#define KEYCODE_PRESSED 2	// Key is only pressed in one frame

#define MOUSE_DOWN(btn) (UPDATE_INFO.mouse.button == btn)
#define KEY_DOWN(name) (UPDATE_INFO.key[ALLEGRO_KEY_##name] & KEYCODE_DOWN)
#define KEY_PRESSED(name) (UPDATE_INFO.key[ALLEGRO_KEY_##name] & KEYCODE_PRESSED)

#define MOUSE_X (UPDATE_INFO.mouse.x)
#define MOUSE_Y (UPDATE_INFO.mouse.y)

#define SCREEN_W (UPDATE_INFO.screenW)
#define SCREEN_H (UPDATE_INFO.screenH)

#define MOUSE (UPDATE_INFO.mouse)
#define CAMERA (UPDATE_INFO.camera)

struct MouseData {
	unsigned int button;
	int x, y;
};

struct UpdateInfo {
	Camera* camera;
	int screenW, screenH;
	MouseData mouse;
	uint8_t key[ALLEGRO_KEY_MAX];
};


extern UpdateInfo UPDATE_INFO;

