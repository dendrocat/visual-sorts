#include "ArgsParser.hpp"

#include <string>

#include <charconv>

bool ArgsParser::help() const noexcept { return _help; }
bool ArgsParser::list() const noexcept { return _list; }

const std::optional<std::string>& ArgsParser::error() const noexcept { return _error; }

const std::optional<int>& ArgsParser::vectorSize() const noexcept { return _vectorSize; }
const std::optional<int>& ArgsParser::gateSteps() const noexcept { return _gateSteps; }
const std::optional<std::string>& ArgsParser::visual() const noexcept { return _visual; }
const std::optional<bool>& ArgsParser::quadratic() const noexcept { return _quadratic; }

bool ArgsParser::parseInt(std::string_view sv, int& out) {
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
	return true;
}

void ArgsParser::parse(const int argc, const char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		const std::string_view arg = argv[i];
		if (arg == "-h" || arg == "--help") {
			_help = true;
			return;
		}
		if (arg == "-l" || arg == "--list") {
			_list = true;
			return;
		}
		if (arg == "--quadratic") {
			_quadratic = true;
			continue;
		}
		if (i + 1 >= argc) {
			_error = "Not enough arguments for " + std::string(arg);
			return;
		}
		++i;
		if (arg == "-v" || arg == "--visual") {
			_visual = std::string_view(argv[i]);
			continue;
		}
		int val;
		if (!parseInt(argv[i], val)) return;
		if (arg == "-s" || arg == "--size") _vectorSize = val;
		else if (arg == "-g" || arg == "--gate") _gateSteps = val;
		else {
			_error = "Unknown option: " + std::string(arg);
			return;
		}
	}
}
