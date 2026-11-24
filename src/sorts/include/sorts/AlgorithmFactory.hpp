#pragma once

#include <macroses.hpp>

#include "SortingAlgorithm.hpp"

#include <functional>
#include <memory>

class AlgorithmFactory {
  private:
	using Creator = std::function<std::unique_ptr<SortingAlgorithm>()>;
	std::vector<Creator> _registry;

	AlgorithmFactory() { }

  public:
	NO_COPY_MOVE(AlgorithmFactory);

	static AlgorithmFactory& instance() {
		static AlgorithmFactory factory;
		return factory;
	}

	void addAlgorithm(Creator creator) { _registry.push_back(std::move(creator)); }

	std::unique_ptr<SortingAlgorithm> create(std::size_t index) {
		if (index >= _registry.size()) return nullptr;
		return _registry[index]();
	}
};
