#include "VectorVisualizer.hpp"

#include <algorithm>

VectorVisualizer::VectorVisualizer(const VectorModel& model) : _model(model) { }

sf::Color VectorVisualizer::getColor(std::size_t i) {
	const sf::Color start = sf::Color::Blue;
	const sf::Color mid = sf::Color::Yellow;
	const sf::Color end = sf::Color::Red;

	const std::size_t n = _model.size();
	float t = (n > 1) ? static_cast<float>(i) / static_cast<float>(n - 1) : 0.f;
	t = std::clamp(t, 0.f, 1.f);

	auto mix = [](const sf::Color& a, const sf::Color& b, float t) -> sf::Color {
		auto lerp = [t](std::uint8_t x, std::uint8_t y) -> std::uint8_t {
			float v = static_cast<float>(x) +
					  (static_cast<float>(y) - static_cast<float>(x)) * t;
			return static_cast<std::uint8_t>(std::clamp(v, 0.f, 255.f) + 0.5f);
		};
		return sf::Color{lerp(a.r, b.r), lerp(a.g, b.g), lerp(a.b, b.b), lerp(a.a, b.a)};
	};

	if (t < 0.5f) return mix(start, mid, t * 2.f);
	else return mix(mid, end, (t - 0.5f) * 2.f);
}

void VectorVisualizer::setSize(const sf::Vector2f& size) {
	_size = size;
	onSetSize();
}

void VectorVisualizer::setPosition(const sf::Vector2f& position) {
	_transform.setPosition(position);
}

void VectorVisualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= _transform.getTransform();
	onDraw(target, states);
}
