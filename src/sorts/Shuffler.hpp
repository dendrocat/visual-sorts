#pragma once

#include "sorts/SortingAlgorithm.hpp"
#include <model/SyncingModel.hpp>
#include <Random.hpp>

class Shuffler final : SortingAlgorithm {
  public:
	const std::string_view name() override { return "Shuffle"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		Random random;
		for (std::size_t i = model->size() - 1; i > 0; --i) {
			model->swap(i, random.get<std::size_t>(0, i));
		}
	}
};
