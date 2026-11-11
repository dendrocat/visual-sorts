#pragma once

#include "VectorVisualizer.hpp"

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>

class Ellipse final : public VectorVisualizer {
  private:
	int max_dist = 0;
	struct Point {
		sf::CircleShape circle;
		float           start;
		float           t = 0.f;

		sf::Vector2f getPosition() { return circle.getPosition(); }
		void         setPosition(sf::Vector2f pos) { circle.setPosition(pos); }
	};
	std::vector<Point> _points;

	const float _radius = 1;
	float       a, b;
	float       angle_step;

	void onSetSize() override;
	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// sf::Vector2f getPos(const float r, const float angle);
	sf::Vector2f getPosition(float r, const float angle);
	float        getRandomStart();

  public:
	Ellipse(const VectorModel& model);

	void update() override;
};
