#pragma once

#include "exceptions/FontNotFoundException.hpp"
#include "model/VectorModel.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

class Statistics final : public sf::Drawable {
	const VectorModel& _model;

	sf::Font _font;
	sf::Text _text;

	std::vector<std::string> lines;

  public:
	Statistics(const VectorModel& model) : _model(model), _text(_font) {

		_text.setFillColor(sf::Color::White);
		lines.resize(5);
		lines[1] = "Vector size: " + std::to_string(_model.size());
	}
	void setFont(const std::string& font) {
		if (!_font.openFromFile(font)) throw FontNotFoundException{font};
	}
	void setSort(const std::string sort) { lines[0] = std::move(sort); }
	void setSize(const unsigned int size) { _text.setCharacterSize(size); }
	void setPosition(const sf::Vector2f pos) { _text.setPosition(pos); }

	void update() {
		lines[2] = "Compares: " + std::to_string(_model.compares());
		lines[3] = "Sets: " + std::to_string(_model.sets());
		lines[4] = "Swaps: " + std::to_string(_model.swaps());

		std::string txt;
		for (const auto& line : lines) txt += line + "\n";
		_text.setString(txt);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_text, states);
	}
};
