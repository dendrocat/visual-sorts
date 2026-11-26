#pragma once

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

class SelectionSort final : public SortingAlgorithm {
  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Selection Sort",
								   .complexity = Complexity::Quad };
		return info;
	}

	void sort(SyncingModel& model) const override {
		for (std::size_t i = 0; i + 1 < model.size(); ++i) {
			auto min = model.get(i);
			auto idx_min = i;
			for (std::size_t j = i + 1; j < model.size(); ++j) {
				if (model.compare(min, model.get(j))) continue;
				min = model.get(j);
				idx_min = j;
			}
			model.swap(i, idx_min);
		}
	}
};

}; // namespace sorts
