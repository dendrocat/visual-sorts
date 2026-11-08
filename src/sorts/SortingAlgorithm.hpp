#pragma once

#include "model/SyncingModel.hpp"
#include <string_view>

class SortingAlgorithm {
  public:
	virtual const std::string_view name() = 0;

	virtual void sort(std::shared_ptr<SyncingModel> model) = 0;

	SortingAlgorithm() = default;
	virtual ~SortingAlgorithm() = default;
	SortingAlgorithm(const SortingAlgorithm&) = delete;
	SortingAlgorithm& operator=(const SortingAlgorithm&) = delete;
};
