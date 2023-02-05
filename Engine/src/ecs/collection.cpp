#include "collection.h"

#include <tuple>
#include <unordered_map>
#include <utility>

#define EXAPMLE true

namespace ecs {
	namespace collection {

		struct CollectionEntry {
			template <typename ...ComponentTypes>
			CollectionEntry() : mask(getComponentMask<ComponentTypes...>()) {
				lists = {
					{ getComponentID<ComponentTypes>(), new std::vector<ComponentTypes>() }...
				};
			}
			// Fix, cant delete unknown type
			//~CollectionEntry() { for (auto& x : lists) delete x.second; }
			
			// Return methods
			template <typename ComponentType>
			std::vector<ComponentType>& getList() const { return static_cast<std::vector<ComponentType>&>(lists.at(getComponentID<ComponentType>()*)); }
			
			const ComponentMask getMask() const { return mask; }

		private:
			ComponentMask mask;
			std::unordered_map<MutableComponentID, void*> lists;
		};

		// Main collection that stores the raw values
		std::vector<CollectionEntry> table;



		struct Entry {
			ComponentMask mask;
			std::unordered_map<MutableComponentID, void*> lists;
		};

		//template <typename ComponentType>
		//std::pair<MutableComponentID, std::vector<ComponentType>> 
		template <typename ComponentType>
		std::pair<ComponentID, std::vector<ComponentType>*> createPair() {
			return std::make_pair(ID<ComponentType>(), new std::vector<ComponentType>());
		}

		template <typename ...ComponentTypes>
		Entry createEntry() {
			Entry entry = {
				// Mask
				getComponentMask<ComponentTypes...>(),
				// Dictionary 
				{
					createPair<ComponentTypes>()...
				}
			}; 
			return entry;
		}

		template <typename ...ComponentTypes>
		std::vector <Result<ComponentTypes...>> query(const ComponentMask targetMask) {
			size_t n = table.size();

			std::vector<Result<ComponentTypes...>> re;
			for (size_t i = 0; i < n; i++) {
				if ((targetMask & table[i].getMask()) == targetMask) {
					Result<ComponentTypes...> result(table[i].getList<ComponentTypes>()...);
					re.push_back(result);
				}
			}
		}

#if EXAMPLE 
		Entry CreateEntry() {
			Entry entry =
			{
				// Mask
				getComponentMask<AA, AB>(),
				// Dictionary 
				{
					{ getComponentID<AA>(), new std::vector<AA>() },
					{ getComponentID<AB>(), new std::vector<AB>() }
				}
			};
		}
		
		struct AA {};
		struct AB {};
		struct AC {};
		struct AD {};
		struct AE {};

		void enter() {
			CollectionEntry aaab = new CollectionEntry();
		}
		std::vector <Result<AA, AB>> query(const ComponentMask targetMask) {
			size_t n = table.size();

			std::vector<Result<AA, AB>> re;
			for (size_t i = 0; i < n; i++) {
				if ((targetMask & table[i].getMask()) == targetMask) {
					Result<AA, AB> result(table[i].getList<AA>(), table[i].getList<AB>());
					re.push_back(result);
				}
			}
		}

#endif
	}
}