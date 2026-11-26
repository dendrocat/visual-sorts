#pragma once

#include <Random.hpp>

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

class Shuffler final : public SortingAlgorithm {
  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Shuffle",
								   .complexity = Complexity::Quad };
		return info;
	}

	void sort(SyncingModel& model) const override {
		Random random;
		for (std::size_t i = model.size() - 1; i > 0; --i) {
			model.swap(i, random.get<std::size_t>(0, i));
		}
	}
};

}; // namespace sorts
