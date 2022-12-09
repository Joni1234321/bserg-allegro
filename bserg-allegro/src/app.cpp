#include "app.h"

#include <stdio.h>
#include <allegro5/allegro5.h>

#include "ecs.h"
#include "ecs/old/helper.h"

#include "overlay/building-overlay.h"

#include "timer.h"

#include "transforms.h"

/// https://coolors.co/ff6700-107ab0-ebebeb-c0c0c0-22181c

App::App(const ALLEGRO_FONT* font) : 
	font(font),
	selection(SelectionBox(camera)),
	game(Game(font, camera))
{
	// Set transforms
	al_identity_transform(&TRANSFORM_UI);
	al_use_transform(&TRANSFORM_UI);

	// Set update info
	CAMERA = &camera;
	
	
	// Other stuff
	selectedUnits.reserve(100);
	
	
	printf("Game Started\n");

	ecs::Start();
}

App::~App()
{
	printf("Game over\n");
}

inline void App::spawnUnit(uint8_t team, uint32_t amount) {
#if DESIGN == OOP
	game.spawnUnit(team, amount);
#else 
	ecs::UnitBatch& batch = ecs::getBatch<ecs::UnitBatch>();
	for (uint32_t i = 0; i < amount; i++)
		ecs::SpawnUnit(batch, float2(300, 300));
#endif
}

void App::input()
{
	if (KEY_PRESSED(ESCAPE)) running = false;
	if (KEY_PRESSED(P)) paused = !paused;

	// LETTERS
	if (KEY_DOWN(B))
		int b = 0;

	// Keyboard
	if (KEY_DOWN(DELETE)) DeleteUnits(ecs::getBatch<ecs::UnitBatch>());

	if (KEY_DOWN(T)) printf("Curry Wurst\n");

	// NUMBES 
	if (KEY_DOWN(1)) spawnUnit(0);
	if (KEY_DOWN(2)) spawnUnit(1);
	if (KEY_PRESSED(3)) {
		static int lastSelectedBuildingType = 0;
		setOverlay<BuildingOverlay>();
		buildingOverlaySelect((BuildingType) (lastSelectedBuildingType++ % (int)BuildingType::COUNT));
	}
	if (KEY_DOWN(4)) spawnUnit(1, 50);
	if (KEY_DOWN(5)) setOverlay<Overlay>();
	if (KEY_DOWN(6)) spawnUnit(1, 1000);
	if (KEY_DOWN(7)) {
		spawnUnit(0, 10000);
		spawnUnit(1, 10000);
	}
	if (KEY_DOWN(8)) {
		spawnUnit(0, 100000);
		spawnUnit(1, 100000);
	}
	if (KEY_DOWN(9)) {
		spawnUnit(0, 1000000);
		spawnUnit(1, 1000000);
	}
	if (KEY_DOWN(0)) {
		spawnUnit(0, 3000000);
		spawnUnit(1, 2000000);
	}
	
	// Scene
	if (KEY_PRESSED(TAB) )
		game.changeScene();

	// Move camera
	cameraDirection = float2(KEY_DOWN(D) - KEY_DOWN(A),KEY_DOWN(W) - KEY_DOWN(S));
}
void App::draw(float t) 
{
	//Timer timer("Draw");
	camera.position = camera.position + (cameraDirection * t * 2 * camera.getInvScale());
	if (MOUSE_SCROLL) {
		float oldScale = camera.getScale();
		float newScale = std::clamp(oldScale + MOUSE_SCROLL * t * .2f, 0.2f, 10.f);
		camera.setScale(newScale);
	}

	al_identity_transform(&TRANSFORM_UI_SCALED);
	al_scale_transform(&TRANSFORM_UI_SCALED, camera.getScale(), camera.getScale());

	al_identity_transform(&TRANSFORM_WORLD);
	al_translate_transform(&TRANSFORM_WORLD, -camera.position.x, camera.position.y);
	al_scale_transform(&TRANSFORM_WORLD, camera.getScale(), camera.getScale());
	
	// invert
	al_copy_transform(&TRANSFORM_WORLD_INVERTED, &TRANSFORM_WORLD);
	al_invert_transform(&TRANSFORM_WORLD_INVERTED);
	//al_draw_text(font, CL_WHITE, camera.position.x + 50, camera.position.y + 20, ALLEGRO_ALIGN_CENTER, game.currentScene().getName());

	// Draw map
	game.draw(t);
#if DESIGN != OOP
	ecs::Update(t, camera);
#endif

	// Then ui
	selection.draw();
}

void App::tick()
{
	if (paused)
		return;

	//Timer timer("Tick");
	ticks++;
	
	// Do map ticks
#if DESIGN == OOP
	game.tick();
#else
	ecs::Tick();
#endif

}


void App::onMouseDown() {
	if (MOUSE_DOWN(MOUSE_LEFT))
		selection.start(UPDATE_INFO.mouse);

	if (MOUSE_DOWN(MOUSE_RIGHT)) {
		ecs::Components<ecs::MoveGoalComponent> moveGoals = ecs::getBatch<ecs::UnitBatch>().moveGoals;
		for (size_t i = 0; i < selectedUnits.size(); i++)
			moveGoals[selectedUnits[i]].goal = camera.screenToWorld(int2(MOUSE_X, MOUSE_Y));
	}
}

bool intersects(const float2& rectHalfSizeWorld, const SelectionBox& selection, const float2 &position) {
	float2 d1 = position - rectHalfSizeWorld;
	float2 d2 = position + rectHalfSizeWorld;

	return selection.intersectsRect(d1.x, d1.y, d2.x, d2.y);
}

bool intersects(const float2 &rectHalfSizeWorld, const SelectionBox& selection, const Unit& unit) {
	float2 d1 = unit.curr - rectHalfSizeWorld;
	float2 d2 = unit.curr + rectHalfSizeWorld;
	
	return selection.intersectsRect(d1.x, d1.y, d2.x, d2.y);
}

void App::onMouseUp() {
	if (MOUSE_DOWN(MOUSE_LEFT))
	{ 
		selection.stop();
		
		ecs::Components<ecs::PositionAnimationComponent> positions = ecs::getBatch<ecs::UnitBatch>().positionAnimations;
		float2 rectHalfSizeWorld = camera.screenToWorld(Unit::halfSize);

		selectedUnits.clear();
		// Get all units selected
		for (uint32_t i = 0; i < positions.size(); i++) {
			if (intersects(rectHalfSizeWorld, selection, positions[i].drawPosition)) {
				selectedUnits.push_back(i);
			}
		}

		printf("Selected Units: %zd\n", selectedUnits.size());
	}
}