#pragma once

#include "SortingAlgorithm.hpp"

class BubbleSort final : public SortingAlgorithm {
  public:
	std::string_view name() override { return "Bubble sort"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		for (std::size_t i = model->size(); i >= 1; --i) {
			auto max = model->get(i - 1);
			auto idx_max = i - 1;
			for (std::size_t j = 0; j < i; ++j) {
				if (model->get(j) <= max) continue;
				max = model->get(j);
				idx_max = j;
			}
			model->swap(i - 1, idx_max);
		}
	}
};
