#include "args/Args.hpp"
#include "args/Usage.hpp"

#include "registery.hpp"
#include "visual.hpp"

#include "Scene.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

void printError(const std::string_view sv) {
	std::cerr << "\033[31m" << sv << "\033[0m\n";
}

int main(const int argc, const char* argv[]) {
	auto parsed = Args::parse(argc, argv);
	if (!parsed) {
		printError(parsed.error().error);
		return 1;
	}
	const Args& args = *parsed;

	if (args.help() || args.list()) {
		if (args.help()) Usage::help();
		if (args.list()) Usage::list();
		return 0;
	}
	visual::Type type = args.type();
	std::size_t  vectorSize = args.vectorSize();
	std::size_t  gateSteps = args.gateSteps();
	bool         quadratic = args.quadratic();

	registerAlgorithms(quadratic);
	registerVisuals();

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.size = mode.size * 80u / 100u;

	sf::RenderWindow window{mode, "sfml", sf::Style::Default, sf::State::Windowed};
	window.setFramerateLimit(60);

	// TODO: remove hardcoded parameters
	constexpr auto font = "/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf";

	Scene scene{type, vectorSize, gateSteps};
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
	return 0;
}
