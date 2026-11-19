#pragma once

#include "defaults.hpp"
#include "visual.hpp"

#include <iomanip>
#include <iostream>

class Usage final {
  public:
	static void help() {
		constexpr std::size_t W = 28;

		auto row = [](const std::string& left, const std::string& right) {
			std::cout << "  " << std::left << std::setw(W) << left << right << "\n";
		};
		std::cout << "Usage: visual-sort\n";
		row("-h, --help", "Show this help");
		row("-l, --list", "Show available visualisations");
		std::cout << "\n";

		std::cout << "Options:\n";
		row("-t, --type <visualisation type>",
			"Set visualisation type (default: " + std::string(defaults::visual) + ")");
		row("-s, --size <size>",
			"Set array size [" + std::to_string(defaults::minVectorSize) + ", " +
				std::to_string(defaults::maxVectorSize) +
				"] (default: " + std::to_string(defaults::vectorSize) + ")");
		row("-g, --gate <steps>",
			"Set steps per frame [" + std::to_string(defaults::minGateSteps) + ", " +
				std::to_string(defaults::maxGateSteps) +
				"] (default: " + std::to_string(defaults::gateSteps) + ")");
		row("--quadratic", "Enalbe quadtatic sorts (default: " +
							   std::to_string(defaults::quadratic) + ")");

		std::cout << "\nExample:\n";
		std::cout << "  visual-sort -v " << defaults::visual << " -s "
				  << defaults::vectorSize << " -g " << defaults::gateSteps << "\n";
	}
	static void list() {
		std::cout << "Available visualisation types:\n";
		for (const auto& vs : visual::visuals) {
			std::cout << "  " << vs.name << "\n";
		}
	}
};
