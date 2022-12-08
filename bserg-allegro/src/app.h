#pragma once
#include <allegro5/allegro_font.h>

#include "engine.h"
#include "inputs.h"

#include "camera.h"

#include "game.h"

#include "ui/selection-box.h"

class App
{
public:
	App(const ALLEGRO_FONT* font);
	~App();

	void update(float t) { 
		input(); 
		draw(t); 
	}
	void tick();


	void onMouseDown();
	void onMouseUp();

	uint64_t getTicks() const { return ticks; }
	Camera& getCamera() { return camera; };
	Game& getGame() { return game; }

	bool running = true;
	bool paused = false;

private:
	void input();
	void draw(float t);

	inline void spawnUnit(uint8_t team, uint32_t amount = 1);

	uint64_t ticks = 0;

		
	// Camera
	Camera camera;
	float2 cameraDirection;


	// UI
	SelectionBox selection;

	// Game
	Game game;

	// Controls
	std::vector<size_t> selectedUnits;
	Unit* selectedUnit;


	// ALLEGRO STUFF
	const ALLEGRO_FONT* font;
};

