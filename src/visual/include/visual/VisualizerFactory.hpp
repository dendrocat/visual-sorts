#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include <VisualType.hpp>
#include <macroses.hpp>

#include <visual/VectorVisualizer.hpp>

class VisualizerFactory {
  private:
	using Creator = std::function<std::unique_ptr<VectorVisualizer>(const VectorModel&)>;
	std::unordered_map<visual::VisualType, Creator> _registry;

	void addVisual(visual::VisualType type, Creator creator);
	void init();

	VisualizerFactory();

  public:
	static const VisualizerFactory& instance();

	std::unique_ptr<VectorVisualizer> create(visual::VisualType       type,
											 const VectorModel& model) const;

	NO_COPY_MOVE(VisualizerFactory);
};
