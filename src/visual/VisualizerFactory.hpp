#pragma once

#include "visual.hpp"

#include "VectorVisualizer.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

class VisualizerFactory {
  private:
	using Creator = std::function<std::unique_ptr<VectorVisualizer>(const VectorModel&)>;
	std::unordered_map<visual::ID, Creator> _registry;

	VisualizerFactory() { }

  public:
	static VisualizerFactory& instance() {
		static VisualizerFactory factory;
		return factory;
	}

	void addVisual(visual::ID id, Creator creator) {
		_registry.emplace(id, std::move(creator));
	}

	std::unique_ptr<VectorVisualizer> create(visual::ID id, const VectorModel& model) {
		if (!_registry.contains(id)) return nullptr;
		return _registry[id](model);
	}

	VisualizerFactory(const VisualizerFactory&) = delete;
	VisualizerFactory& operator=(const VisualizerFactory&) = delete;
	VisualizerFactory(VisualizerFactory&&) = delete;
	VisualizerFactory& operator=(VisualizerFactory&&) = delete;
};
