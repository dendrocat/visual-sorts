#pragma once

#include "VisualType.hpp"
#include "model/SyncingModel.hpp"
#include "visual/Statistics.hpp"
#include "visual/VectorVisualizer.hpp"

#include "SortingManager.hpp"

#include <SFML/Graphics/Drawable.hpp>

class Scene final : public sf::Drawable {
  private:
	std::shared_ptr<SyncingModel> _model;

	std::unique_ptr<Statistics>       _stat;
	std::unique_ptr<VectorVisualizer> _visual;

	std::unique_ptr<SortingManager> _sorting;

  public:
	Scene(VisualType type, const std::size_t vectorSize, const std::size_t gateSteps);
	NO_COPY_MOVE(Scene);

	void setSize(sf::Vector2u windowSize);
	void setFont(const std::string& font);

	void start();
	void update();
	void close();

  protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
