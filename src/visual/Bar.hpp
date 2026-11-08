#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "VectorVisualizer.hpp"

class Bar final : public VectorVisualizer {
  private:
	sf::RectangleShape              _rect;
	std::vector<sf::RectangleShape> _bars;

	void onSetSize() override;
	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

  public:
	Bar(const VectorModel& model);

	void update(bool isSorting) override;
};
