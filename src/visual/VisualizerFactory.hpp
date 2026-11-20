#pragma once

#include "macroses.hpp"

#include "visual.hpp"

#include "VectorVisualizer.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

class VisualizerFactory {
  private:
	using Creator = std::function<std::unique_ptr<VectorVisualizer>(const VectorModel&)>;
	std::unordered_map<visual::Type, Creator> _registry;

	VisualizerFactory() { }

  public:
	static VisualizerFactory& instance() {
		static VisualizerFactory factory;
		return factory;
	}

	void addVisual(visual::Type type, Creator creator) {
		_registry.emplace(type, std::move(creator));
	}

	std::unique_ptr<VectorVisualizer> create(visual::Type       type,
											 const VectorModel& model) {
		if (!_registry.contains(type)) return nullptr;
		return _registry[type](model);
	}

	NO_COPY_MOVE(VisualizerFactory);
};
