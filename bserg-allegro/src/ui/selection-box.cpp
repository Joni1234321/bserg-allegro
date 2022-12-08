#include "selection-box.h"

#include <allegro5/mouse.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include "colors.h"



void SelectionBox::start(const MouseData& mouse) {

	active = true;	
	startScreen = int2(mouse.x, mouse.y);
	startWorld = camera.screenToWorld(startScreen);
}

void SelectionBox::draw() {
	if (active) {
		ALLEGRO_MOUSE_STATE mouse;
		al_get_mouse_state(&mouse);
		currWorld = camera.screenToWorld(int2(mouse.x, mouse.y));

		
		// Sort top and bottom
		if (currWorld.x < startWorld.x) {
			topLeft.x = currWorld.x;
			bottomRight.x = startWorld.x;
		}
		else {
			topLeft.x = startWorld.x;
			bottomRight.x = currWorld.x;
		}

		if (currWorld.y < startWorld.y) {
			topLeft.y = currWorld.y;
			bottomRight.y = startWorld.y;
		}
		else {
			topLeft.y = startWorld.y;
			bottomRight.y = currWorld.y;
		}


		const int thickness = 2, thr = thickness * 2;

		if (fabs(mouse.x - startScreen.x) < thr && fabs(mouse.y - startScreen.y) < thr)
			return;

		//al_draw_filled_rectangle(x, y, mouse.x, mouse.y, CL_ORANGE_HALF);
		al_draw_rectangle(startScreen.x, startScreen.y, mouse.x, mouse.y, CL_ORANGE, thickness);
	}
}


bool SelectionBox::intersectsRect(float x1,float y1,float x2,float y2) const {
	return 	
		(topLeft.x < x2 && bottomRight.x > x1 &&
			topLeft.y < y2 && bottomRight.y > y1);
}