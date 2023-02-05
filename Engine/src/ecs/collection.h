#pragma once
#include "shared.h"

#include <vector>
#include <tuple>

namespace ecs {
	namespace collection {

		template <typename ...ComponentTypes>
		struct Result {
		public:

			Result(std::vector<ComponentTypes>& lists...) : tuple(std::make_tuple(lists...)) {}

			// Return the vector of the given type
			template <typename ComponentType>
			const std::vector<ComponentType>& get() {
				return std::get<std::vector<ComponentType>&>(tuple);
			}
		private:
			std::tuple <std::vector<ComponentTypes>&...> tuple;
			
		};

		template <typename ...ComponentTypes>
		std::vector <Result<ComponentTypes...>> query(const ComponentMask targetMask);
	}
}
