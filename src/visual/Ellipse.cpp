#include "Ellipse.hpp"

#include "Random.hpp"

Ellipse::Ellipse(const VectorModel& model)
	: VectorVisualizer(model), _points(model.size()) {
	for (std::size_t i = 0; i < _points.size(); ++i) {
		auto& p = _points[i];

		p.circle.setRadius(_radius);
		p.circle.setOrigin({_radius, _radius});
		p.circle.setFillColor(getColor(i));
	}
	static constexpr float pi = std::numbers::pi_v<float>;
	angle_step = 2 * pi / model.size();
}

void Ellipse::onSetSize() {
	this->a = _size.x / 2, this->b = _size.y / 2;

	for (std::size_t i = 0; i < _points.size(); ++i) {
		const float angle = angle_step * i;

		_points[i].setPosition(getPosition(1, angle));
	}
}

void Ellipse::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& p : _points) target.draw(p.circle, states);
}

float Ellipse::getRandomStart() {
	static thread_local Random random;
	return random.get(0.01f, 0.99f);
}

float getDeg(const float rad, const float pi) { return rad * 180 / pi; }

sf::Vector2f Ellipse::getPosition(float r, const float angle) {
	return {r * std::cos(angle) * this->a, r * std::sin(angle) * this->b};
}

void Ellipse::update() {
	const int n = _points.size();
	max_dist = _model.size();

	for (int i = 0; i < n; ++i) {
		if (!_model.markered(i)) continue;
		auto& p = _points[_model.get(i)];

		p.t = std::abs(_model.get(i) - i) / static_cast<float>(max_dist);
		p.t = std::min(1.f, 1 - p.t);

		p.setPosition(getPosition(p.t, angle_step * i));
	}
}
