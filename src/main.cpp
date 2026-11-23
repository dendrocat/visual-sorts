#include "Options.hpp"
#include "args/Args.hpp"
#include "args/Usage.hpp"

#include "Registry.hpp"

#include "app/Scene.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string_view>

void printError(const std::string_view sv) {
	std::cerr << "\033[31m" << sv << "\033[0m\n";
}

int main(const int argc, const char* argv[]) {
	auto expectedOptions = Args::parse(argc, argv);
	if (!expectedOptions) {
		printError(expectedOptions.error().message);
		return 1;
	}
	const Options& options = expectedOptions.value();

	if (options.help || options.list) {
		if (options.help) Usage::help();
		if (options.list) Usage::list();
		return 0;
	}
	VisualType  type = options.type;
	std::size_t vectorSize = options.vectorSize;
	std::size_t gateSteps = options.gateSteps;
	bool        quadratic = options.quadratic;

	Registry::init(quadratic);

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
