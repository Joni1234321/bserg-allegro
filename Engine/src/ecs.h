#pragma once
#include <assert.h>
#include <stdint.h>
#include <vector>

// Inspiration https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html#:~:text=Using%20the%20ECS%20framework%20we'll%20make&text=Components%20are%20just%20plain%20old,us%20access%20and%20manage%20it.

// List of batches
// Every batch contains list of components
// Every entity all the components at that index, therefore all entities that are in the same batch has the same components
// Components contains data only

// Systems are created for each entity

namespace ecs {
	struct ECSManager {
		static ECSManager& instance() { static ECSManager _instance(64); return _instance; }
		std::vector<void*> batches;
	private:
		ECSManager(size_t reserved) {
			batches.reserve(reserved);
		}
	};

	// SingleTon
	extern uint32_t _batchIdCounter;
	template <typename T>
	inline uint32_t getBatchId() {
		static const uint32_t batchId = _batchIdCounter++;
		return batchId;
	}

	template <typename T>
	inline void addBatch(T* batch) {
		static const uint32_t batchId = getBatchId<T>();

		// Only ever add it once
		assert(ECSManager::instance().batches.size() == batchId);

		ECSManager::instance().batches.push_back(batch);
	}

	template <typename T>
	inline T& getBatch() {
		static const uint32_t batchId = getBatchId<T>();

		assert(ECSManager::instance().batches[batchId] != NULL);
		return (*static_cast<T*>(ECSManager::instance().batches[batchId]));
	}



}

