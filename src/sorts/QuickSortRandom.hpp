#pragma once

#include <Random.hpp>

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

class QuickSortRandom final : public SortingAlgorithm {

	std::size_t partition(SyncingModel& model, const std::size_t l,
						  const std::size_t r) const {
		static Random random;
		auto          pivot = model.get(random.get(l, r));

		std::size_t i = l, j = r;
		while (1) {
			while (i <= r && model.compare(model.get(i), pivot)) ++i;
			while (j >= l && model.compare(pivot, model.get(j))) --j;
			if (i >= j) return j;
			model.swap(i, j);
			++i, --j;
		}
	}

	void quicksort(SyncingModel& model, const std::size_t l, const std::size_t r) const {
		if (l >= r) return;
		std::size_t i = partition(model, l, r);
		quicksort(model, l, i);
		quicksort(model, i + 1, r);
	}

  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Quick Sort Random",
								   .complexity = Complexity::NLogN };
		return info;
	}

	void sort(SyncingModel& model) const override {
		quicksort(model, 0, model.size() - 1);
	}
};

}; // namespace sorts
