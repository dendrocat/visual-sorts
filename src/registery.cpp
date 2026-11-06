#include "registery.hpp"
#include "sorts/AlgorithmFactory.hpp"

#include "sorts/BubbleSort.hpp"
#include "sorts/SelectionSort.hpp"

#include <memory>

void registerAlgorithms() {
	auto &f = AlgorithmFactory::instance();

	f.add_algorithm([]() { return std::make_unique<BubbleSort>(); });
	f.add_algorithm([]() { return std::make_unique<SelectionSort>(); });
}
