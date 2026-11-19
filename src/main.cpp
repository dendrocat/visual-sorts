#include "Scene.hpp"
#include "args/Args.hpp"
#include "registery.hpp"
#include "visual.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

void printError(const std::string_view sv) {
	std::cerr << "\033[31m" << sv << "\033[0m\n";
}

int main(const int argc, const char* argv[]) {
	visual::ID  visual;
	std::size_t vectorSize;
	std::size_t gateSteps;
	bool        quadratic;
	{
		Args args{argc, argv};
		if (!args.errors().empty()) {
			for (const auto& e : args.errors()) printError(e);
			return 1;
		}
		if (args.help() || args.list()) {
			if (args.help()) args.printHelp();
			if (args.list()) args.printList();
			return 0;
		}

		visual = args.visual();
		vectorSize = args.vectorSize();
		gateSteps = args.gateSteps();
		quadratic = args.quadratic();
	}

	registerAlgorithms(quadratic);
	registerVisuals();

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode.size = mode.size * 80u / 100u;

	sf::RenderWindow window{mode, "sfml", sf::Style::Default, sf::State::Windowed};
	window.setFramerateLimit(60);

	// TODO: remove hardcoded parameters
	constexpr auto font = "/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf";

	Scene scene{visual, vectorSize, gateSteps};
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
