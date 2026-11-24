#include <visual/VisualizerFactory.hpp>

#include "Bar.hpp"
#include "Ellipse.hpp"

VisualizerFactory::VisualizerFactory() { init(); }

void VisualizerFactory::addVisual(VisualType type, Creator creator) {
	_registry.emplace(type, std::move(creator));
}

void VisualizerFactory::init() {
	addVisual(VisualType::Bar,
			  [](const VectorModel& model) { return std::make_unique<Bar>(model); });
	addVisual(VisualType::Ellipse,
			  [](const VectorModel& model) { return std::make_unique<Ellipse>(model); });
}

const VisualizerFactory& VisualizerFactory::instance() {
	static VisualizerFactory factory;
	return factory;
}

std::unique_ptr<VectorVisualizer>
VisualizerFactory::create(VisualType type, const VectorModel& model) const {
	if (!_registry.contains(type)) return nullptr;
	return _registry.at(type)(model);
}
