#include "ecs.h"
#include "ecs-add.h"
#include "system.h"
#include "archetype.h"
// Inspiration https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html#:~:text=Using%20the%20ECS%20framework%20we'll%20make&text=Components%20are%20just%20plain%20old,us%20access%20and%20manage%20it.

// List of batches
// Every batch contains list of components
// Every entity all the components at that index, therefore all entities that are in the same batch has the same components
// Components contains data only

// Systems are created for each entity

namespace ecs {
	ComponentID component_id = 0;
	EntityTypeID entity_type_id = 0;
	EntityID entityIDCounter = 0;

	uint32_t _batchIdCounter = 0;


	struct P { int x, y; };
	struct V { int x, y; };

	Archetype<P, V> fisk;
	void test() {
		fisk.add();
	}

	struct FiskSystem : System<P, V> {
		virtual void Do(std::vector<P>& p, std::vector<V>& v, size_t n) {
			for (size_t i = 0; i < n; i++) {
				P& pos = p[i];
				V& vel = v[i];
			}
		}
	};
}