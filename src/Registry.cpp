#include "Registry.hpp"

#include "sorts/AlgorithmFactory.hpp"

#include "sorts/BubbleSort.hpp"
#include "sorts/MergeSort.hpp"
#include "sorts/QuickSortDualPivot.hpp"
#include "sorts/QuickSortHoare.hpp"
#include "sorts/QuickSortLomuto.hpp"
#include "sorts/QuickSortRandom.hpp"
#include "sorts/SelectionSort.hpp"

#include "VisualType.hpp"
#include "visual/VisualizerFactory.hpp"

#include "visual/Bar.hpp"
#include "visual/Ellipse.hpp"

#include <memory>

void Registry::registerAlgorithms(bool quadratic) {
	auto& f = AlgorithmFactory::instance();

	if (quadratic) {
		f.addAlgorithm([]() { return std::make_unique<BubbleSort>(); });
		f.addAlgorithm([]() { return std::make_unique<SelectionSort>(); });
	}
	f.addAlgorithm([]() { return std::make_unique<MergeSort>(); });
	f.addAlgorithm([]() { return std::make_unique<QuickSortLomuto>(); });
	f.addAlgorithm([]() { return std::make_unique<QuickSortHoare>(); });
	f.addAlgorithm([]() { return std::make_unique<QuickSortRandom>(); });
	f.addAlgorithm([]() { return std::make_unique<QuickSortDualPivot>(); });
}

void Registry::registerVisuals() {
	auto& f = VisualizerFactory::instance();

	f.addVisual(VisualType::Bar,
				[](const VectorModel& model) { return std::make_unique<Bar>(model); });
	f.addVisual(VisualType::Ellipse, [](const VectorModel& model) {
		return std::make_unique<Ellipse>(model);
	});
}

void Registry::init(bool quadratic) {
	registerAlgorithms(quadratic);
	registerVisuals();
}
