#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "../model/VectorModel.hpp"

class VectorVisualizer : public sf::Drawable {
  protected:
	const VectorModel& _model;

	sf::Transformable _transform;
	sf::Vector2f      _size;

	sf::Color getColor(std::size_t i);

	virtual void onSetSize() = 0;
	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

  public:
	VectorVisualizer(const VectorModel& model);

	void setSize(const sf::Vector2f& size);
	void setPosition(const sf::Vector2f& position);

	virtual void update() = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	virtual ~VectorVisualizer() = default;
	VectorVisualizer(const VectorVisualizer&) = delete;
	VectorVisualizer& operator=(const VectorVisualizer&) = delete;
};
