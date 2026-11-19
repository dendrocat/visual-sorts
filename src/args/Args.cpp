#include "Args.hpp"

#include "defaults.hpp"
#include "exceptions/ArgsErrors.hpp"
#include "visual.hpp"

#include <iomanip>
#include <iostream>
#include <string>

Args::Args(const int argc, const char* argv[]) {
	_parser.parse(argc, argv);
	if (_parser.help() || _parser.list()) return;
	_validator.validate(_parser);
}

std::expected<Args, ArgsError> Args::parse(const int argc, const char* argv[]) {
	try {
		return Args{argc, argv};
	}
	catch (const ParseError& e) {
		return std::unexpected<ArgsError>{std::move(e.what())};
	}
	catch (const ValidationError& e) {
		return std::unexpected<ArgsError>{std::move(e.what())};
	}
}

std::size_t  Args::vectorSize() const noexcept { return _validator.vectorSize(); }
std::size_t  Args::gateSteps() const noexcept { return _validator.gateSteps(); }
visual::Type Args::visual() const noexcept { return _validator.visual(); }
bool         Args::quadratic() const noexcept { return _validator.quadratic(); }

bool Args::help() const noexcept { return _parser.help(); }
bool Args::list() const noexcept { return _parser.list(); }

void Args::printHelp() {
	constexpr std::size_t W = 28;

	auto row = [](const std::string& left, const std::string& right) {
		std::cout << "  " << std::left << std::setw(W) << left << right << "\n";
	};
	std::cout << "Usage: visual-sort\n";
	row("-h, --help", "Show this help");
	row("-l, --list", "Show available visualisations");
	std::cout << "\n";

	std::cout << "Options:\n";
	row("-s, --size <size>",
		"Set array size [" + std::to_string(defaults::minVectorSize) + ", " +
			std::to_string(defaults::maxVectorSize) +
			"] (default: " + std::to_string(defaults::vectorSize) + ")");
	row("-g, --gate <steps>",
		"Set steps per frame [" + std::to_string(defaults::minGateSteps) + ", " +
			std::to_string(defaults::maxGateSteps) +
			"] (default: " + std::to_string(defaults::gateSteps) + ")");
	row("-v, --visual <visual>",
		"Set visualisation (default: " + std::string(defaults::visual) + ")");
	row("--quadratic",
		"Enalbe quadtatic sorts (default: " + std::to_string(defaults::quadratic) + ")");

	std::cout << "\nExample:\n";
	std::cout << "  visual-sort -v " << defaults::visual << " -s " << defaults::vectorSize
			  << " -g " << defaults::gateSteps << "\n";
}

void Args::printList() {
	std::cout << "Available visualisations:\n";
	for (const auto& vs : visual::visuals) {
		std::cout << "  " << vs.name << "\n";
	}
}
