#include <visual/VisualizerFactory.hpp>

#include "Bar.hpp"
#include "Ellipse.hpp"

VisualizerFactory::VisualizerFactory() { init(); }

void VisualizerFactory::addVisual(visual::VisualType type, Creator creator) {
	_registry.emplace(type, std::move(creator));
}

void VisualizerFactory::init() {
	addVisual(visual::VisualType::Bar,
			  [](const VectorModel& model) { return std::make_unique<Bar>(model); });
	addVisual(visual::VisualType::Ellipse,
			  [](const VectorModel& model) { return std::make_unique<Ellipse>(model); });
}

const VisualizerFactory& VisualizerFactory::instance() {
	static VisualizerFactory factory;
	return factory;
}

std::unique_ptr<VectorVisualizer>
VisualizerFactory::create(visual::VisualType type, const VectorModel& model) const {
	if (!_registry.contains(type)) return nullptr;
	return _registry.at(type)(model);
}
