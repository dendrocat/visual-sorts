#include "ArgsParser.hpp"

#include "exceptions/ArgsErrors.hpp"

#include <charconv>
#include <string>

bool ArgsParser::help() const noexcept { return _help; }
bool ArgsParser::list() const noexcept { return _list; }

const std::optional<int>& ArgsParser::vectorSize() const noexcept { return _vectorSize; }
const std::optional<int>& ArgsParser::gateSteps() const noexcept { return _gateSteps; }
const std::optional<std::string>& ArgsParser::visual() const noexcept { return _visual; }
const std::optional<bool>& ArgsParser::quadratic() const noexcept { return _quadratic; }

int ArgsParser::parseInt(std::string_view sv) {
	auto end = sv.data() + sv.size();
	int  res;
	auto [ptr, ec] = std::from_chars(sv.data(), end, res);

	if (ec == std::errc::invalid_argument)
		throw ParseError("Not a number: '" + std::string(sv) + "'");
	if (ec == std::errc::result_out_of_range)
		throw ParseError("Number out of range: '" + std::string(sv) + "'");
	if (ptr != end)
		throw ParseError("Trailing characters in number: '" + std::string(sv) + "'");
	return res;
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
			throw ParseError("Not enough arguments for '" + std::string(arg) + "'");
			return;
		}
		++i;
		if (arg == "-v" || arg == "--visual") {
			_visual = std::string_view(argv[i]);
			continue;
		}
		int val = parseInt(argv[i]);
		if (arg == "-s" || arg == "--size") _vectorSize = val;
		else if (arg == "-g" || arg == "--gate") _gateSteps = val;
		else throw ParseError("Unknown option '" + std::string(arg) + "'");
	}
}
