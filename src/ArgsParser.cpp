#include "ArgsParser.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#include <charconv>
#include <cstring>
#include <system_error>

ArgsParser::ArgsParser(const int argc, const char* argv[])
	: _vectorSize(_defaultVectorSize), _gateSteps(_defaultGateSteps),
	  _visual(_defaultVisual) {
	parse(argc, argv);
}

void ArgsParser::printHelp() const noexcept {
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
		"Set array size (default: " + std::to_string(_defaultVectorSize) + ")");
	row("-g, --gate <steps>",
		"Set steps per frame (default: " + std::to_string(_defaultGateSteps) + ")");
	row("-v, --visual <visual>",
		"Set visualisation (default: " + std::string(_defaultVisual) + ")");

	std::cout << "\nExample:\n";
	std::cout << "  visual-sort -v ellipse -s 1000 -g 5\n";
}
bool ArgsParser::checkVisual(std::string_view candidate) const noexcept {
	for (auto& v : visuals) {
		if (candidate == v) return true;
	}
	return false;
}
void ArgsParser::printVisualList() const noexcept {
	std::cout << "Available visualisations:\n";
	for (auto v : visuals) {
		std::cout << "  " << v << "\n";
	}
}
bool ArgsParser::help() const noexcept {
	if (_help) printHelp();
	if (_list) printVisualList();
	return _help || _list;
}
bool ArgsParser::error() const noexcept {
	if (_error.empty()) return false;
	std::cerr << "\033[31m" << _error << "\033[0m\n";
	if (_list) printVisualList();
	return true;
}

std::string_view ArgsParser::visual() const noexcept { return _visual; }
std::size_t      ArgsParser::vectorSize() const noexcept { return _vectorSize; }
std::size_t      ArgsParser::gateSteps() const noexcept { return _gateSteps; }

bool ArgsParser::parseSizeT(std::string_view sv, std::size_t& out) {
	auto end = sv.data() + sv.size();
	auto [ptr, ec] = std::from_chars(sv.data(), end, out);

	if (ec == std::errc::invalid_argument) {
		_error = "Not a number: '" + std::string(sv) + "'";
		return false;
	}
	if (ec == std::errc::result_out_of_range) {
		_error = "Number out of range: '" + std::string(sv) + "'";
		return false;
	}
	if (ptr != end) {
		_error = "Trailing characters in number: '" + std::string(sv) + "'";
		return false;
	}
	if (out == 0) {
		_error = "Value must be >= 1";
		return false;
	}
	return true;
}

void ArgsParser::parse(const int argc, const char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		const std::string_view arg = argv[i++];
		if (arg == "-h" || arg == "--help") {
			_help = true;
			return;
		}
		if (arg == "-l" || arg == "--list") {
			_list = true;
			return;
		}
		if (i >= argc) {
			_error = "Not enough arguments for " + std::string(arg);
			if (arg == "-v" || arg == "--visual") _list = true;
			return;
		}
		if (arg == "-v" || arg == "--visual") {
			auto vis = std::string_view(argv[i]);
			if (checkVisual(vis)) _visual = argv[i];
			else {
				_error = "Visualisation " + std::string(vis) + " doesn't supported";
				_list = true;
				return;
			}
			continue;
		}
		std::size_t val;
		if (!parseSizeT(argv[i], val)) return;
		if (arg == "-s" || arg == "--size") _vectorSize = val;
		else if (arg == "-g" || arg == "--gate") _gateSteps = val;
	}
}
