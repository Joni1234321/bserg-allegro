#include "systems.h"

#include <cmath>
#include "threads/BS_thread_pool.hpp"
#include "transforms.h"

using namespace ecs; 

// 6 m animations Parrallel = 150 ms, Normal = 450 ms
// 200k animations 50 ms
#define P false // PARR
#define S 0 //SIMD
#if P
BS::thread_pool pool(std::thread::hardware_concurrency() - 1);
#endif 

void UnitDrawSystem(UnitBatch& batch, float t, const Camera& camera) {
	al_use_transform(&TRANSFORM_WORLD);
	//ALLEGRO_SHADER_GLSL
	// TODO SET TIME STEP HERE
	// TODO IMPLEMENT READONLY AND WRITEONLY OPTIONS FOR OPTIMIZATIONS WHEN DOING PARRALLEL

	Components<PositionComponent>& positions = batch.positions;
	Components<PositionNextComponent>& nextPositions = batch.nextPositions;
	Components<PositionAnimationComponent>& animations = batch.positionAnimations;
	Components<UnitEnabledComponentsComponent>& enabledComponents = batch.enabledComponents;
	size_t n = positions.size();

	static ALLEGRO_COLOR unitColor = al_map_rgb(235 - 100, 235, 235);
	static int2 unitHalfSize(15, 10);
	static ALLEGRO_BITMAP* bm = al_create_bitmap(unitHalfSize.x, unitHalfSize.y);
	static bool first = true;
	if (first) {
		first = false;
		al_set_target_bitmap(bm);
		for (int y = 0; y < unitHalfSize.y; y++)
			for (int x = 0; x < unitHalfSize.x; x++)
				al_put_pixel(x, y, CL_FULL_WHITE);
		al_unlock_bitmap(bm);
	}



	/*ALLEGRO_COLOR* teamColors = new ALLEGRO_COLOR[2];
	for (uint8_t i = 0; i < 2; i++)
		teamColors[i] = al_map_rgb(235 - 100 * (i + 1), 235 - 50 * i, 235 - 80 * i);
		*/

#if P && S == 0
	auto loop = [&positions, &animations, &camera, t](const int a, const int b) {
		float2 unitHalfSizeScreen = float2(unitHalfSize.x, unitHalfSize.y);
		for (int i = a; i < b; i++) {
			PositionComponent& position = positions[i];
			PositionAnimationComponent& animation = animations[i];

			animation.drawPosition = lerp(position.current, position.next, t);
			int2 d1 = camera.worldToScreen(animation.drawPosition - unitHalfSizeScreen);
			int2 d2 = camera.worldToScreen(animation.drawPosition + unitHalfSizeScreen);
			//al_draw_filled_rectangle(d1.x, d1.y, d2.x, d2.y, unitColor);
		}
	};

	pool.parallelize_loop(0, n, loop, 16).wait();
#else
	float2 unitHalfSizeScreen = float2(unitHalfSize.x, unitHalfSize.y);

#if S 
	static const int instructionSize = 256; // SIZE OF SIMD
	static const int floatsPerSIMD = instructionSize / (sizeof(float) * 8); // 8 floats per SIMD 256 instructions
	size_t i = 0;
	size_t iterations = n < floatsPerSIMD * 2 ? 0 : n - floatsPerSIMD * 2 + 1;
#endif

#if S == 0
	al_hold_bitmap_drawing(true);

	// Maybe do this
	for (int i = 0; i < n; i++) {
		//UnitEnabledComponentsComponent enabled = enabledComponents[i];

		//if (enabled.positionAnimation) {
		PositionAnimationComponent& animation = animations[i];
		
		PositionComponent& position = positions[i];
		PositionNextComponent& nextPosition = nextPositions[i];

		animation.drawPosition = lerp(position.current, nextPosition.next, t);
		
		// Maybe do this in another
		//int2 d1 = camera.worldToScreen(animation.drawPosition - unitHalfSizeScreen);
		//int2 d2 = camera.worldToScreen(animation.drawPosition + unitHalfSizeScreen);
		//float scale = camera.getInvScale();
		al_draw_tinted_bitmap(bm, unitColor, animation.drawPosition.x, animation.drawPosition.y, 0);
		//al_draw_tinted_scaled_bitmap(bm, unitColor, 0, 0, unitHalfSize.x, unitHalfSize.y, animation.drawPosition.x, animation.drawPosition.y, unitHalfSize.x * scale, unitHalfSize.y * scale, NULL);
		//al_draw_filled_rectangle(d1.x, d1.y, d2.x, d2.y, unitColor);
		//}
	}

	al_hold_bitmap_drawing(false);

#elif S == 1

	__m256 tplus = _mm256_set1_ps(t);
	__m256 tminus = _mm256_set1_ps(-t);
	
	for (; i < iterations; i += floatsPerSIMD * 2) {

		__m256 regA = _mm256_loadu_ps(&positions[i].current.x);
		__m256 regB = _mm256_loadu_ps(&nextPositions[i].next.x);

		__m256 regA2 = _mm256_loadu_ps(&positions[i + floatsPerSIMD].current.x);
		__m256 regB2 = _mm256_loadu_ps(&nextPositions[i + floatsPerSIMD].next.x);

		//fma(t, v1, fma(-t, v0, v0))
		__m256 p1 = _mm256_fmadd_ps(tminus, regA, regA);
		__m256 p2 = _mm256_fmadd_ps(tminus, regA2, regA2);

		__m256 lerpVal = _mm256_fmadd_ps(tplus, regB, p1);
		__m256 lerpVal2 = _mm256_fmadd_ps(tplus, regB2, p2);

		_mm256_storeu_ps(&animations[i].drawPosition.x, lerpVal);
		_mm256_storeu_ps(&animations[i + floatsPerSIMD].drawPosition.x, lerpVal2);
	}
#else
	for (; i < iterations; i += bytes) {
		lerp256(&positions[i].current.x, &nextPositions[i].next.x, t, &animations[i].drawPosition.x);
	}
#endif

#if S
	for (; i < n; i++) {
		PositionComponent& position = positions[i];
		PositionNextComponent& nextPosition = nextPositions[i];
		PositionAnimationComponent& animation = animations[i];

		animation.drawPosition = lerp(position.current, nextPosition.next, t);
	}

	al_hold_bitmap_drawing(true);

	// Maybe do this
	for (int i = 0; i < n; i++) {
		//UnitEnabledComponentsComponent enabled = enabledComponents[i];

		//if (enabled.positionAnimation) {
		PositionAnimationComponent& animation = animations[i];
		al_draw_tinted_bitmap(bm, unitColor, animation.drawPosition.x, animation.drawPosition.y, 0);

		/*
		PositionComponent& position = positions[i];
		PositionNextComponent& nextPosition = nextPositions[i];

		animation.drawPosition = lerp(position.current, nextPosition.next, t);
		*/
		// Maybe do this in another
		//int2 d1 = camera.worldToScreen(animation.drawPosition - unitHalfSizeScreen);
		//int2 d2 = camera.worldToScreen(animation.drawPosition + unitHalfSizeScreen);
		//al_draw_filled_rectangle(d1.x, d1.y, d2.x, d2.y, unitColor);
		//}
	}

	al_hold_bitmap_drawing(false);
#endif
	
#endif
}


void UnitStateSystem(UnitBatch& batch) {
	Components<PositionComponent>& positions = batch.positions;
	Components<PositionNextComponent>& nextPositions = batch.nextPositions;
	Components<PositionAnimationComponent>& animations = batch.positionAnimations;
	Components<MoveGoalComponent>& moveGoals = batch.moveGoals;
	Components<AttackComponent>& attacks = batch.attacks;
	Components<UnitEnabledComponentsComponent>& enabledComponents = batch.enabledComponents;

	size_t n = positions.size();

	
	static const int bytes = 32;
	size_t i = 0;
	size_t iterations = n < bytes ? 0 : n - bytes - 1;
	

	static const float speed = 8, speedSqr = speed * speed;

#if false
	for (; i < iterations; i += bytes) {

		float k = speed * rsqrt(distSqr);
		position.current = nextPosition.next;

		nextPosition.next.x += d.x * k;
		nextPosition.next.y += d.y * k;
	}
#endif
	// Maybe do this
	for (; i < n; i++) {
		UnitEnabledComponentsComponent enabled = enabledComponents[i];

		// Move system
		if (enabled.moveGoal) {
			PositionComponent& position = positions[i];
			PositionNextComponent& nextPosition = nextPositions[i];
			MoveGoalComponent& moveGoal = moveGoals[i];

			position.current = nextPosition.next;

			float2 d = moveGoal.goal - nextPosition.next;
			float distSqr = d.distSqr();

			if (distSqr > speedSqr) {
				float k = speed * rsqrt(distSqr);

				nextPosition.next.x += d.x * k;
				nextPosition.next.y += d.y * k;
			}
			else {
				nextPosition.next = moveGoal.goal;
				enabled.moveGoal = false;
			}
		}

		// Attack system
		//if (enabled.attack) {
		//	PositionComponent& position = positions[i];
		//	AttackComponent& attack = attacks[i];

			// Reaload / midfire 
			//if (enabled.shooting)


		//	if (!enabled.target) {
				// Look for new target
		//	}


		//}

		
		static UnitEnabledComponentsComponent actionMask = { false, true, true, false };
		bool idle = (actionMask.mask & enabled.mask) == 0;
		if (idle) {
			moveGoals[i].goal = float2(200 + rand() % 200, 200 + rand() % 200);
			enabled.moveGoal = true;
		}

	}
}
