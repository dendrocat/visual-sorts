#include "VectorVisualizer.hpp"

VectorVisualizer::VectorVisualizer(const VectorModel& model) : _model(model) {}

void VectorVisualizer::setPosition(const sf::Vector2f& position) {
	_transform.setPosition(position);
}

void VectorVisualizer::setSize(const sf::Vector2f& size) {
	_size = size;
	onSetSize();
}

void VectorVisualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= _transform.getTransform();
	onDraw(target, states);
}
