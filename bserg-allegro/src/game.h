#pragma once
#include <allegro5/allegro_font.h>

#include "ecs/old/unit.h"
#include "models/world.h"
#include "overlay/overlay.h"

#include <vector>

#include "camera.h"

class Game {
public:
	Game(const ALLEGRO_FONT*,const Camera&);
	~Game();

	const uint8_t n_teams = 2;
	std::vector<Unit>* units;
	ALLEGRO_COLOR* team_colors;


	// Builtin
	void tick();
	void draw(float t);

	// My functions
	void spawnUnit(uint8_t team, uint32_t amount = 1);
	void changeScene();

	const Scene& currentScene () const { return scenes[sceneI]; }
private:

	void load();

	const ALLEGRO_FONT* font;

	// Camera
	const Camera& camera;

	// World
	World world;


	// Scenes
	Scene* scenes;
	uint32_t sceneI, sceneN;

};