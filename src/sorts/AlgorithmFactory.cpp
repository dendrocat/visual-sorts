#include "sorts/AlgorithmFactory.hpp"

#include <memory>

#include "Shuffler.hpp"

#include "BubbleSort.hpp"
#include "SelectionSort.hpp"

#include "MergeSort.hpp"
#include "QuickSortDualPivot.hpp"
#include "QuickSortHoare.hpp"
#include "QuickSortLomuto.hpp"
#include "QuickSortRandom.hpp"

using namespace sorts;

#define ENTRY_CREATOR(Algorithm)                                  \
	Entry {                                                       \
		.complexity = Algorithm{}.info().complexity,              \
		.creator = []() { return std::make_unique<Algorithm>(); } \
	}

void AlgorithmFactory::init() {
	_registry.push_back(ENTRY_CREATOR(BubbleSort));
	_registry.push_back(ENTRY_CREATOR(SelectionSort));
	_registry.push_back(ENTRY_CREATOR(MergeSort));
	_registry.push_back(ENTRY_CREATOR(QuickSortLomuto));
	_registry.push_back(ENTRY_CREATOR(QuickSortHoare));
	_registry.push_back(ENTRY_CREATOR(QuickSortRandom));
	_registry.push_back(ENTRY_CREATOR(QuickSortDualPivot));
};

AlgorithmFactory::AlgorithmFactory() { init(); }

AlgorithmFactory& AlgorithmFactory::instance() {
	static AlgorithmFactory factory;
	return factory;
}

void AlgorithmFactory::filter(Complexity complexity) {
	std::erase_if(_registry, [&complexity](Entry& e) {
		return (e.complexity & complexity) == Complexity::None;
	});
}

std::unique_ptr<SortingAlgorithm> AlgorithmFactory::shuffler() {
	return std::make_unique<Shuffler>();
}

std::unique_ptr<SortingAlgorithm> AlgorithmFactory::create(std::size_t index) {
	if (index >= _registry.size()) return nullptr;
	return _registry[index].creator();
}
