#pragma once

#include <vector>

#include "VectorVisualizer.hpp"

class Ellipse final : public VectorVisualizer {
  private:
	static constexpr float pi = std::numbers::pi_v<float>;
	int                    max_dist = 0;
	struct Point {
		sf::CircleShape circle;
		// x - radius, y - angle
		sf::Vector2f start, end;
		float t = 0.f, t2 = 0.f;

		sf::Vector2f getPosition() { return circle.getPosition(); }
		void         setPosition(sf::Vector2f pos) { circle.setPosition(pos); }
	};
	std::vector<Point> _points;
	const float        _radius = 1;
	float              a, b;

	void onSetSize() override;
	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getLerpedPosition(sf::Vector2f a, sf::Vector2f b, float t);
	void         setRandomPosition(Point& point);

  public:
	Ellipse(const VectorModel& model);

	void update(bool isSorting) override;
};
