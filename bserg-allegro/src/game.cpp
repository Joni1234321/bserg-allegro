#include "game.h"

#include "engine.h"

#include <cassert>
#include <allegro5/allegro_primitives.h>

#include "bserg.h"
#include "globals.h"

#include "ecs.h"
#include "models/world.h"
#include "models/building.h"
#include "models/worker.h"

#include "overlay/overlay.h"
#include "overlay/battle-overlay.h"
#include "overlay/building-overlay.h"

#include "bserg\images.h"
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
	addOverlay<BattleOverlay>(new BattleOverlay());
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
#if DESIGN == OOP

	// Update position
	for (uint8_t t = 0; t < n_teams; t++) {
		for (uint32_t i = 0; i < units[t].size(); i++) {
			if (moveUnitTick(units[t][i]))
				units[t][i].goal = float2(rand() % 1000, rand() % 1000);
		}
	}
#endif
	bserg::worker::tick(world);
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
	const Tile2 mouseTile(Unit2(mouseCoords.x, mouseCoords.y));


	// Buildings
	const int nBuildings = (const int)bserg::world.buildings.size();
	
	// Building Collision
	static const Building * selectedBuilding = NULL;
	static Unit2 selectedCorner1, selectedCorner2;

	const Building* hoverBuilding = NULL;
	Unit2 hoverCorner1, hoverCorner2;

	for (int i = 0; i < nBuildings; i++) {
		const Building& building = bserg::world.buildings[i];
		Unit2 position = drawBuilding(building);
	
		// Already detected
		if (hoverBuilding)
			continue;

		// Get collision with building
		Tile2 size = getSpec(building.type)->size;
		Tile2 corner = building.topLeftTile + size;
		if (collision::insideRect(mouseTile.x, mouseTile.y, building.topLeftTile.x, building.topLeftTile.y, corner.x - 1, corner.y - 1)) {
			hoverBuilding = &building;
			hoverCorner1 = position;
			hoverCorner2 = Unit2(corner);

			// Set building
			if (MOUSE_PRESSED(MOUSE_LEFT)) {
				printf("selected\n");
				selectedBuilding = &building;
				selectedCorner1 = position;
				selectedCorner2 = Unit2(corner);
			}
		}
	}

	bserg::worker::drawAll();

	// Draw outer rect around hovering building
	if (hoverBuilding)
		al_draw_rectangle(hoverCorner1.x, hoverCorner1.y, hoverCorner2.x, hoverCorner2.y, CL_ORANGE, 2);

	// Draw thicker outline on selected building
	if (selectedBuilding) {
		al_draw_rectangle(selectedCorner1.x, selectedCorner1.y, selectedCorner2.x, selectedCorner2.y, CL_ORANGE, 4);
	}


	// Draw selected tile
	{
		const Unit2 snappedMouse(mouseTile);
		al_draw_rectangle(snappedMouse.x, snappedMouse.y, snappedMouse.x + UNITS_PER_TILE, snappedMouse.y + UNITS_PER_TILE, CL_GREY, 2);
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
	// Load images
	bserg::images::load();

	loadSpecs();
}

