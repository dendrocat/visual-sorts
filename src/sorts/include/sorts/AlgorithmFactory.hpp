#pragma once

#include <functional>
#include <memory>

#include <macroses.hpp>

#include <Complexity.hpp>

#include "SortingAlgorithm.hpp"

namespace sorts
{

class AlgorithmFactory {
  private:
	using Creator = std::function<std::unique_ptr<SortingAlgorithm>()>;
	struct Entry {
		Complexity complexity;
		Creator    creator;
	};
	std::vector<Entry> _registry;

	void addAlgorithm(Creator creator);
	void init();
	AlgorithmFactory();

  public:
	NO_COPY_MOVE(AlgorithmFactory);

	static AlgorithmFactory& instance();

	void filter(Complexity complexity);

	std::unique_ptr<SortingAlgorithm> shuffler();

	std::unique_ptr<SortingAlgorithm> create(std::size_t index);
};

}; // namespace sorts
