#include "registery.hpp"

#include "sorts/AlgorithmFactory.hpp"

#include "sorts/BubbleSort.hpp"
#include "sorts/MergeSort.hpp"
#include "sorts/QuickSortDualPivot.hpp"
#include "sorts/QuickSortHoare.hpp"
#include "sorts/QuickSortLamuto.hpp"
#include "sorts/QuickSortRandom.hpp"
#include "sorts/SelectionSort.hpp"

#include <memory>

void registerAlgorithms() {
	auto& f = AlgorithmFactory::instance();

	// f.add_algorithm([]() { return std::make_unique<BubbleSort>(); });
	// f.add_algorithm([]() { return std::make_unique<SelectionSort>(); });
	// f.add_algorithm([]() { return std::make_unique<MergeSort>(); });
	f.add_algorithm([]() { return std::make_unique<QuickSortLamuto>(); });
	// f.add_algorithm([]() { return std::make_unique<QuickSortHoare>(); });
	// f.add_algorithm([]() { return std::make_unique<QuickSortRandom>(); });
	f.add_algorithm([]() { return std::make_unique<QuickSortDualPivot>(); });
}
