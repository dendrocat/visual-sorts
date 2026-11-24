#pragma once

#include <macroses.hpp>

#include <VisualType.hpp>

#include "VectorVisualizer.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

class VisualizerFactory {
  private:
	using Creator = std::function<std::unique_ptr<VectorVisualizer>(const VectorModel&)>;
	std::unordered_map<VisualType, Creator> _registry;

	void addVisual(VisualType type, Creator creator);
	void init();

	VisualizerFactory();

  public:
	static const VisualizerFactory& instance();

	std::unique_ptr<VectorVisualizer> create(VisualType         type,
											 const VectorModel& model) const;

	NO_COPY_MOVE(VisualizerFactory);
};
