#pragma once

#include "model/SyncingModel.hpp"
#include "sorts/SortingManager.hpp"
#include "visual/Statistics.hpp"
#include "visual/VectorVisualizer.hpp"

#include <SFML/Graphics/Drawable.hpp>

class Scene final : public sf::Drawable {
  private:
	std::shared_ptr<SyncingModel> _model;

	std::unique_ptr<Statistics>       _stat;
	std::unique_ptr<VectorVisualizer> _visual;

	std::unique_ptr<SortingManager> _sorting;

  public:
	Scene(const std::string visualName, const std::size_t vectorSize = 1000,
		  const std::size_t gateSteps = 5);

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;

	void setSize(sf::Vector2u windowSize);
	void setFont(const std::string& font);

	void start();
	void update();
	void close();

  protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
