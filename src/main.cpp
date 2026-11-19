#include "ArgsParser.hpp"
#include "Scene.hpp"
#include "registery.hpp"

#include <SFML/Graphics.hpp>

int main(const int argc, const char* argv[]) {
	ArgsParser parser{argc, argv};
	if (parser.error()) return -1;
	if (parser.help()) return 0;
	registerAlgorithms();
	registerVisuals();

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.size = mode.size / 100u * 80u;

	sf::RenderWindow window{mode, "sfml", sf::Style::Default, sf::State::Windowed};
	window.setFramerateLimit(60);

	// TODO: remove hardcoded parameters
	constexpr auto font = "/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf";

	Scene scene{parser.visual(), parser.vectorSize(), parser.gateSteps()};
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
