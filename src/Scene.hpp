#pragma once

#include "model/SyncingModel.hpp"
#include "sorts/SortingManager.hpp"
#include "Statistics.hpp"
#include "visual/VectorVisualizer.hpp"

#include <SFML/Graphics/Drawable.hpp>

class Scene final : public sf::Drawable {
  private:
	static constexpr size_t _vectorSize = 1000;

	std::shared_ptr<SyncingModel>     _model;
	std::unique_ptr<Statistics>       _stat;
	std::unique_ptr<VectorVisualizer> _visual;
	std::unique_ptr<SortingManager>   _sorting;

  public:
	Scene(sf::Vector2u windowSize);

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;

	void start();
	void update();
	void close();

  protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
