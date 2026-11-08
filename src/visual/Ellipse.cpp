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
}

void Ellipse::onSetSize() {
	this->a = _size.x / 2, this->b = _size.y / 2;
	const float angle_step = 2.0f * Ellipse::pi / _points.size();

	for (std::size_t i = 0; i < _points.size(); ++i) {
		const float angle = angle_step * i - Ellipse::pi;

		sf::Vector2f pos(std::cos(angle), std::sin(angle));

		_points[i].end = {std::hypot(pos.x, pos.y), std::atan2(pos.y, pos.x)};
		pos.x *= this->a;
		pos.y *= this->b;
		_points[i].setPosition(pos);
	}
}

void Ellipse::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& p : _points) target.draw(p.circle, states);
}

void Ellipse::setRandomPosition(Point& point) {
	static thread_local Random random;

	auto pos = point.getPosition();

	const float angle = random.get(-Ellipse::pi, Ellipse::pi);

	const float u = random.get(0.0f, 1.0f);
	pos.x = u * std::cos(angle);
	pos.y = u * std::sin(angle);

	point.start = {std::hypot(pos.x, pos.y), std::atan2(pos.y, pos.x)};
	pos.x *= this->a;
	pos.y *= this->b;
	point.setPosition(pos);
}

sf::Vector2f Ellipse::getLerpedPosition(sf::Vector2f a, sf::Vector2f b, float t) {
	float dangle = b.y - a.y;
	if (dangle > Ellipse::pi) dangle -= 2 * Ellipse::pi;
	if (dangle < -Ellipse::pi) dangle += 2 * Ellipse::pi;
	sf::Vector2f pol{a.x + (b.x - a.x) * t, a.y + dangle * t};
	return {pol.x * std::cos(pol.y) * this->a, pol.x * std::sin(pol.y) * this->b};
}

void Ellipse::update(bool isSorting) {
	const int n = _points.size();

	for (int i = 0; i < n; ++i) {
		if (!_model.markered(i)) continue;
		max_dist = std::max(max_dist, std::abs(_model.get(i) - i));
	}
	for (int i = 0; i < n; ++i) {
		auto& p = _points[_model.get(i)];
		if (!isSorting) {
			max_dist = 0;
			p.t = p.t2 = 0;
			if (!_model.markered(i)) continue;
			setRandomPosition(p);
		}
		else {
			if (_model.markered(i)) {
				auto  dist = std::abs(_model.get(i) - i);
				float t = 1 - std::clamp(static_cast<float>(dist) / max_dist, 0.f, 1.f);
				p.t = std::max(t, p.t);
			}
			p.t2 += (p.t - p.t2) * 0.4f;
			p.setPosition(getLerpedPosition(p.start, p.end, p.t2));
		}
	}
}
