#pragma once

#include <vector>

#include "VectorVisualizer.hpp"

class Ellipse final : public VectorVisualizer {
  private:
	const float _radius = 10;
	std::vector<sf::CircleShape> _points;

	void onSetSize() override;

	void onDraw(sf::RenderTarget &target,
				sf::RenderStates states) const override;

  public:
	Ellipse(const VectorModel &model);

	void update() override;
};
