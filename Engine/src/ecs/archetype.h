#pragma once

#include "ecs-add.h"

namespace ecs {
	// Arcetype
	template<typename... ComponentTypes>
	// So each entity can be combined into a entity set, which would be nice
	class Archetype {
	public:
		Archetype() { }
		EntityID add() {
			for (uint32_t i = 0; i < n; i++) {
			//	components[i].emplace_back();
			}
			return 0;
		}
		// todo: remove, void remove(EntityID);
	private:
		inline static int n = sizeof...(ComponentTypes);
		
	};
}