#pragma once

#include <bitset>
#include <vector>

namespace ecs {
	#define MAX_COMPONENTS 256
	typedef std::bitset<MAX_COMPONENTS> ComponentMask;

	typedef uint8_t MutableComponentID;
	typedef const MutableComponentID ComponentID;
	typedef uint32_t EntityID;
	typedef uint16_t EntityTypeID;

	extern ComponentID component_id;

	// Only way to get id of component
	template <typename ComponentType>
	ComponentID getComponentID() {
		static ComponentID id = component_id++;
		return id;
	}


	// Only way to create the ComponentMask
	template<typename ...ComponentTypes> 
	ComponentMask getComponentMask() {
		ComponentMask mask;
		ComponentID ids[] = { GetID<ComponentTypes>() ... };
		for (size_t i = 0; i < sizeof...(ComponentTypes); i++) 
			mask.set(ids[i]);
		return mask;
	}


}