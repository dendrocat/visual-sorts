#include "Scene.hpp"

#include "visual/Ellipse.hpp"
#include <string>

Scene::Scene(sf::Vector2u windowSize)
	: _model(std::make_shared<SyncingModel>(_vectorSize)) {
	_sorting = std::make_unique<SortingManager>(_model);

	_visual = std::make_unique<Ellipse>(_model->container());
	_visual->setSize({windowSize.x * 0.90f, windowSize.y * 0.90f});
	_visual->setPosition({windowSize.x / 2.0f, windowSize.y / 2.0f});

	_stat = std::make_unique<Statistics>(_model->container(), std::string("/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf"));
	_stat->setPosition({0, 0});
	_stat->setSize(24);
}

void Scene::start() { _sorting->start(); }

void Scene::update() {
	_model->lock();
	_stat->setSort(_sorting->algorithmName());
	_stat->update();
	_visual->update();
	_model->clearMarkers();
	_model->unlock();
}

void Scene::close() { _sorting->stop(); }

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	_visual->draw(target, states);
	_stat->draw(target, states);
}
