#pragma once

#include <model/SyncingModel.hpp>
#include <random>

class Shuffler {
  public:
	void shuffle(std::shared_ptr<SyncingModel> model) {
		std::mt19937 rng(std::random_device{}());
		for (std::size_t i = model->size() - 1; i > 0; --i) {
			std::uniform_int_distribution<size_t> dist(0, i);
			model->swap(i, dist(rng));
		}
	}
};
