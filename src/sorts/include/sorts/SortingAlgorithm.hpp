#pragma once

#include <string_view>

#include <macroses.hpp>

#include <Complexity.hpp>

#include <model/SyncingModel.hpp>

namespace sorts
{

struct AlgorithmInfo {
	std::string_view name;

	Complexity complexity;
};

class SortingAlgorithm {
  public:
	SortingAlgorithm() = default;
	NO_COPY_MOVE(SortingAlgorithm);
	virtual ~SortingAlgorithm() = default;

	[[nodiscard]] virtual const AlgorithmInfo& info() const noexcept = 0;

	virtual void sort(SyncingModel& model) const = 0;
};

}; // namespace sorts
