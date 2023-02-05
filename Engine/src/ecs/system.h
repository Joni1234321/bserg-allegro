#pragma once

#include "collection.h"
#include "shared.h"

namespace ecs {
	template <typename... ComponentTypes>
	class System {
	public:

		System() : componentMask(getComponentMask<ComponentTypes...>()) {
			updateCollectionReferences();
		}

		void updateCollectionReferences() {
			collectionReferences = collection::get(componentMask);
		}

		void tick() {
			for (size_t i = 0; i < collectionReferences.size(); i++) {
				Do(collectionReferences[i].get<ComponentTypes>()..., collectionReferences[i].size());
			}

		}
	protected:
		virtual void Do(const std::vector<ComponentTypes>& ..., size_t n) = 0;
	private:
		size_t n = sizeof...(ComponentTypes);

		ComponentMask componentMask;
		std::vector<collection::CollectionReference<ComponentTypes...>> collectionReferences;

	};


}