#pragma once

#include <model/SyncingModel.hpp>
#include <Random.hpp>

class Shuffler {
  public:
	void shuffle(std::shared_ptr<SyncingModel> model) {
		Random random;
		for (std::size_t i = model->size() - 1; i > 0; --i) {
			model->swap(i, random.get<std::size_t>(0, i));
		}
	}
};
