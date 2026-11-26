#pragma once

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

// TODO: Write BubbleSort xD
class BubbleSort final : public SortingAlgorithm {
  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Bubble Sort",
								   .complexity = Complexity::Quad };
		return info;
	}

	void sort(SyncingModel& model) const override {
		for (std::size_t i = model.size(); i >= 1; --i) {
			auto max = model.get(i - 1);
			auto idx_max = i - 1;
			for (std::size_t j = 0; j < i; ++j) {
				if (model.compare(model.get(j), max)) continue;
				max = model.get(j);
				idx_max = j;
			}
			model.swap(i - 1, idx_max);
		}
	}
};

}; // namespace sorts
