#include "registery.hpp"

#include "sorts/AlgorithmFactory.hpp"

#include "sorts/BubbleSort.hpp"
#include "sorts/MergeSort.hpp"
#include "sorts/QuickSortDualPivot.hpp"
#include "sorts/QuickSortHoare.hpp"
#include "sorts/QuickSortLomuto.hpp"
#include "sorts/QuickSortRandom.hpp"
#include "sorts/SelectionSort.hpp"

#include "visual/Bar.hpp"
#include "visual/Ellipse.hpp"
#include "visual/VisualizerFactory.hpp"

#include <memory>

void registerAlgorithms() {
	auto& f = AlgorithmFactory::instance();

	// f.add_algorithm([]() { return std::make_unique<BubbleSort>(); });
	// f.add_algorithm([]() { return std::make_unique<SelectionSort>(); });
	// f.add_algorithm([]() { return std::make_unique<MergeSort>(); });
	f.add_algorithm([]() { return std::make_unique<QuickSortLomuto>(); });
	// f.add_algorithm([]() { return std::make_unique<QuickSortHoare>(); });
	// f.add_algorithm([]() { return std::make_unique<QuickSortRandom>(); });
	f.add_algorithm([]() { return std::make_unique<QuickSortDualPivot>(); });
}

void registerVisuals() {
	auto& f = VisualizerFactory::instance();

	f.add_visual("bar",
				 [](const VectorModel& model) { return std::make_unique<Bar>(model); });
	f.add_visual("ellipse", [](const VectorModel& model) {
		return std::make_unique<Ellipse>(model);
	});
}
