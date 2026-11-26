#pragma once

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

class QuickSortDualPivot final : public SortingAlgorithm {

	std::pair<std::size_t, std::size_t>
	partition(SyncingModel& model, const std::size_t l, const std::size_t r) const {
		if (model.compare(model.get(r), model.get(l))) model.swap(l, r);

		auto p1 = model.get(l), p2 = model.get(r);
		auto less_pivot1 = l + 1, greater_pivot2 = r - 1;
		auto i = less_pivot1;
		while (i <= greater_pivot2) {
			if (model.compare(model.get(i), p1)) {
				model.swap(i, less_pivot1);
				++less_pivot1;
			}
			else if (model.compare(p2, model.get(i))) {
				model.swap(greater_pivot2, i);
				--greater_pivot2;
				--i;
			}
			++i;
		}
		--less_pivot1, ++greater_pivot2;
		model.swap(less_pivot1, l);
		model.swap(greater_pivot2, r);
		return { less_pivot1, greater_pivot2 };
	}

	void quicksort(SyncingModel& model, const std::size_t l, const std::size_t r) const {
		if (r - l < 2) return;
		auto [p1, p2] = partition(model, l, r - 1);
		quicksort(model, l, p1);
		quicksort(model, p1 + 1, p2);
		quicksort(model, p2 + 1, r);
	}

  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Quick Sort Dual Pivot",
								   .complexity = Complexity::NLogN };
		return info;
	}

	void sort(SyncingModel& model) const override { quicksort(model, 0, model.size()); }
};

}; // namespace sorts
