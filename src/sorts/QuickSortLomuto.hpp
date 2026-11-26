#pragma once

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

class QuickSortLomuto final : public SortingAlgorithm {
	std::shared_ptr<SyncingModel> _model;

	std::size_t partition(SyncingModel& model, const std::size_t l,
						  const std::size_t r) const {
		auto pivot = model.get(r);

		std::size_t i = l;
		for (std::size_t j = l; j < r; ++j) {
			if (!model.compare(model.get(j), pivot)) continue;
			model.swap(i, j);
			++i;
		}
		model.swap(i, r);
		return i;
	}

	void quicksort(SyncingModel& model, const std::size_t l, const std::size_t r) const {
		if (r - l < 2) return;
		std::size_t i = partition(model, l, r - 1);
		quicksort(model, l, i);
		quicksort(model, i + 1, r);
	}

  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Quick Sort Lomuto",
								   .complexity = Complexity::NLogN };
		return info;
	}

	void sort(SyncingModel& model) const override { quicksort(model, 0, model.size()); }
};

}; // namespace sorts
