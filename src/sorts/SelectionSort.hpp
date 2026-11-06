#pragma once

#include "SortingAlgorithm.hpp"

class SelectionSort final : public SortingAlgorithm {
  public:
	std::string_view name() override { return "Selection sort"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		for (std::size_t i = 0; i + 1 < model->size(); ++i) {
			int min = model->get(i);
			std::size_t idx_min = i;
			for (std::size_t j = i + 1; j < model->size(); ++j) {
				if (min <= model->get(j)) continue;
				min = model->get(j);
				idx_min = j;
			}
			model->swap(i, idx_min);
		}
	}
};
