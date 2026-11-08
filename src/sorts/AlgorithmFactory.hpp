#pragma once

#include "SortingAlgorithm.hpp"

#include <functional>
#include <memory>
#include <utility>

class AlgorithmFactory {
  private:
	using Creator = std::function<std::unique_ptr<SortingAlgorithm>()>;
	std::vector<Creator> _registry;

	AlgorithmFactory() {}

  public:
	static AlgorithmFactory& instance() {
		static AlgorithmFactory factory;
		return factory;
	}

	void add_algorithm(Creator creator) { _registry.push_back(std::move(creator)); }

	std::unique_ptr<SortingAlgorithm> create(std::size_t index) {
		if (index >= _registry.size()) return nullptr;
		return _registry[index]();
	}

	AlgorithmFactory(const AlgorithmFactory&) = delete;
	AlgorithmFactory& operator=(const AlgorithmFactory&) = delete;
	AlgorithmFactory(AlgorithmFactory&&) = delete;
	AlgorithmFactory& operator=(AlgorithmFactory&&) = delete;
};
