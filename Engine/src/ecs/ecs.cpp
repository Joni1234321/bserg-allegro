#include "ecs.h"

// Inspiration https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html#:~:text=Using%20the%20ECS%20framework%20we'll%20make&text=Components%20are%20just%20plain%20old,us%20access%20and%20manage%20it.

// List of batches
// Every batch contains list of components
// Every entity all the components at that index, therefore all entities that are in the same batch has the same components
// Components contains data only

// Systems are created for each entity

namespace ecs {
	uint32_t _batchIdCounter = 0;
}