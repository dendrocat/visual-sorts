#include "Scene.hpp"
#include "registery.hpp"

#include <SFML/Graphics.hpp>

int main() {
	registerAlgorithms();
	registerVisuals();

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.size = mode.size / 100u * 80u;

	sf::RenderWindow window{mode, "sfml", sf::Style::Default, sf::State::Windowed};
	window.setFramerateLimit(60);

	// TODO: remove hardcoded parameters 
	constexpr std::size_t vectorSize = 1000;
	constexpr std::size_t gateSteps = 5;
	constexpr auto font =
		"/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf";
	Scene scene{"ellipse", vectorSize, gateSteps};
	scene.setSize(mode.size);
	scene.setFont(font);
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
