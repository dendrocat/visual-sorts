#pragma once

#include "VectorVisualizer.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

class VisualizerFactory {
  private:
	using Creator = std::function<std::unique_ptr<VectorVisualizer>(const VectorModel&)>;
	std::unordered_map<std::string, Creator> _registry;

	VisualizerFactory() { }

  public:
	static VisualizerFactory& instance() {
		static VisualizerFactory factory;
		return factory;
	}

	void addVisual(std::string name, Creator creator) {
		_registry.emplace(name, std::move(creator));
	}

	std::unique_ptr<VectorVisualizer> create(const std::string  name,
											 const VectorModel& model) {
		if (!_registry.contains(name)) return nullptr;
		return _registry[name](model);
	}

	VisualizerFactory(const VisualizerFactory&) = delete;
	VisualizerFactory& operator=(const VisualizerFactory&) = delete;
	VisualizerFactory(VisualizerFactory&&) = delete;
	VisualizerFactory& operator=(VisualizerFactory&&) = delete;
};
