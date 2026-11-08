#include "Bar.hpp"

Bar::Bar(const VectorModel& model) : VectorVisualizer(model) {
	_bars = std::vector<sf::RectangleShape>(_model.size(), sf::RectangleShape({10, 10}));
	for (std::size_t i = 0; i < _bars.size(); ++i) {
		auto& bar = _bars[i];
		bar.setFillColor(getColor(i));
		bar.setOutlineColor(sf::Color::Black);
		bar.setOutlineThickness(1);
	}

	_rect.setFillColor(sf::Color::Transparent);
	_rect.setOutlineColor(sf::Color::White);
	_rect.setOutlineThickness(2);
}

void Bar::onSetSize() {
	_rect.setSize(_size);
	_rect.setOrigin(_size / 2.0f);

	const float width = _size.x / _model.size();
	const float height_step = _size.y / _model.size();

	for (size_t i = 0; i < _bars.size(); ++i) {
		const float height = std::min((i + 1) * height_step, _size.y);

		_bars[i].setSize({width, height});
		_bars[i].setPosition({i * width - _size.x / 2, _size.y / 2 - height});
	}
}
void Bar::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& p : _bars) target.draw(p, states);
	target.draw(_rect, states);
}

void Bar::update(bool _) {
	const float width = _size.x / _model.size();
	for (size_t i = 0; i < _bars.size(); ++i) {
		auto& bar = _bars[_model.get(i)];

		auto p = bar.getPosition();
		p.x = i * width - _size.x / 2;

		bar.setPosition(p);
	}
}
