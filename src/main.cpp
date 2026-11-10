#include "registery.hpp"
#include "Scene.hpp"

#include <SFML/Graphics.hpp>

int main() {
	registerAlgorithms();

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.size = mode.size / 100u * 80u;

	sf::RenderWindow window{mode, "sfml", sf::Style::Default, sf::State::Windowed};
	window.setFramerateLimit(60);

	Scene scene{mode.size};
	scene.start();

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				scene.close();
				window.close();
			}
		}
		scene.update();

		window.clear(sf::Color::Black);
		window.draw(scene);
		window.display();
	}
}
