#include "game.h"

#include "engine.h"

#include <cassert>
#include <allegro5/allegro_primitives.h>

#include "bserg.h"
#include "globals.h"

#include "ecs.h"
#include "models\world.h"
#include "models/building.h"

#include "overlay/overlay.h"
#include "overlay/building-overlay.h"

#include "inputs.h"
#include "collision.h"
#include "transforms.h"
#include "timer.h"

#include <iostream>


Game::Game(const ALLEGRO_FONT* font, const Camera& camera) :
	font(font),
	camera(camera),
	world(World()),
	scenes{ new Scene[]{Scene("Base"), Scene("Objectives")} }, sceneI(0), sceneN(2)
{
	TIMER("Game");

	load();

	// Create UI
	addOverlay(new Overlay());
	addOverlay<BuildingOverlay>(new BuildingOverlay());
	setOverlay<Overlay>();

	// Create teams
	units = new std::vector<Unit>[n_teams];
	team_colors = new ALLEGRO_COLOR[n_teams];

	for (int i = 0; i < n_teams; i++) {

		units[i] = std::vector<Unit>();
		units[i].reserve(300);

		team_colors[i] = al_map_rgb(235 - 100 * (i + 1), 235 - 50 * i, 235 - 80 * i);
	}

}

Game::~Game()
{
	delete[] team_colors;
	delete[] units;
}

void Game::tick()
{
	// Update position
	for (uint8_t t = 0; t < n_teams; t++) {
		for (uint32_t i = 0; i < units[t].size(); i++) {
			if (moveUnitTick(units[t][i]))
				units[t][i].goal = float2(rand() % 1000, rand() % 1000);
		}
	}
}

void Game::draw(float t)
{
#if DESIGN == OOP
	// Draw units
	static int2 unitHalfSize(15, 10);
	float2 unitHalfSizeScreen = float2(unitHalfSize.x * camera.getScale(), unitHalfSize.y * camera.getScale());

	for (uint8_t team = 0; team < n_teams; team++) {
		for (uint32_t i = 0; i < units[team].size(); i++) {
			Unit& unit = units[team][i];
			unit.drawPosition = lerp(unit.curr, unit.next, t);
			int2 d1 = camera.worldToScreen(unit.drawPosition - unitHalfSizeScreen);
			int2 d2 = camera.worldToScreen(unit.drawPosition + unitHalfSizeScreen);
			al_draw_filled_rectangle(d1.x, d1.y, d2.x, d2.y, team_colors[team]);
		}
	}
#endif


	// draw buildings
	al_use_transform(&TRANSFORM_WORLD);

	// Mouse
	float2 mouseCoords = float2(MOUSE_X, MOUSE_Y);
	al_transform_coordinates(&TRANSFORM_WORLD_INVERTED, &mouseCoords.x, &mouseCoords.y);
	const int2 mouseTile = UNIT_TO_TILE(int2(mouseCoords.x, mouseCoords.y));


	// Buildings
	const int nBuildings = bserg::world.buildings.size();
	
	// Building Collision
	bool buildingCollision = false;
	int2 collisionCorner1, collisionCorner2;

	for (int i = 0; i < nBuildings; i++) {
		const Building& building = bserg::world.buildings[i];
		int2 unitPos = TILE_TO_UNIT(building.topLeftTile);

		// Draw building
		al_draw_bitmap(getSpec(building.type)->bitmap, unitPos.x, unitPos.y, 0);

		// Already detected
		if (buildingCollision)
			continue;

		// Get collision with building
		int2 size = getSpec(building.type)->size;
		int2 corner = building.topLeftTile + size;
		if (collision::insideRect(mouseTile.x, mouseTile.y, building.topLeftTile.x, building.topLeftTile.y, corner.x - 1, corner.y - 1)) {
			buildingCollision = true;
			collisionCorner1 = unitPos;
			collisionCorner2 = TILE_TO_UNIT(corner);
		}
	
	}

	// Draw outer rect around hovering building
	if (buildingCollision)
		al_draw_rectangle(collisionCorner1.x, collisionCorner1.y, collisionCorner2.x, collisionCorner2.y, CL_ORANGE, 6);

	// Draw selected tile
	{
		const int2 snappedMouse = TILE_TO_UNIT(mouseTile);
		al_draw_rectangle(snappedMouse.x, snappedMouse.y, snappedMouse.x + 64, snappedMouse.y + 64, CL_GREY, 4);
	}




	getCurrentOverlay()->draw();

}

void Game::spawnUnit(uint8_t team, uint32_t amount)
{
	assert(team < n_teams);
	printf("Spawning %d units at: %d %d\n", amount, 300, 300);

	for (uint32_t i = 0; i < amount; i++) {
		units[team].emplace_back(float2{ 300, 300 });
		units[team][units[team].size() - 1].goal = float2(250, 250);
	}
}

void Game::changeScene() {
	sceneI = (sceneI + 1) % sceneN;
}


void Game::load() {
	loadSpecs();
}