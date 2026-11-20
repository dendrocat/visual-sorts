#pragma once

#include "macroses.hpp"

#include "model/SyncingModel.hpp"

#include <string_view>

class SortingAlgorithm {
  public:
	SortingAlgorithm() = default;
	NO_COPY_MOVE(SortingAlgorithm);
	virtual ~SortingAlgorithm() = default;

	virtual const std::string_view name() = 0;

	virtual void sort(std::shared_ptr<SyncingModel> model) = 0;
};
