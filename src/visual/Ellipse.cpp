#include "Ellipse.hpp"

Ellipse::Ellipse(const VectorModel& model) : VectorVisualizer(model) {
	_points = std::vector<sf::CircleShape>(_model.size(), sf::CircleShape(_radius));
	for (auto& p : _points) p.setOrigin({_radius, _radius});
}

void Ellipse::onSetSize() {
	constexpr float pi = std::numbers::pi_v<float>;
	const float     angle_step = 2.0f * pi / _points.size();

	for (size_t i = 0; i < _points.size(); ++i) {
		const float angle = angle_step * i;

		const sf::Vector2f pos(_size.x / 2 * std::cos(angle),
							   _size.y / 2 * std::sin(angle));

		_points[i].setPosition(pos);
	}
}

void Ellipse::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& p : _points) target.draw(p, states);
}
