#include "ArgsParser.hpp"

#include "exceptions/ArgsErrors.hpp"
#include "options.hpp"

#include <charconv>
#include <string>

bool ArgsParser::help() const noexcept { return _help; }
bool ArgsParser::list() const noexcept { return _list; }

const std::optional<int>& ArgsParser::vectorSize() const noexcept { return _vectorSize; }
const std::optional<int>& ArgsParser::gateSteps() const noexcept { return _gateSteps; }
const std::optional<std::string>& ArgsParser::type() const noexcept { return _type; }
const std::optional<bool>& ArgsParser::quadratic() const noexcept { return _quadratic; }

int ArgsParser::parseInt(std::string_view sv) const {
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

		auto optionSpec = options::findOption(arg);
		if (optionSpec == nullptr)
			throw ParseError("Unknown option '" + std::string(arg) + "'");

		if (optionSpec->type == options::Type::Value) {
			if (i + 1 >= argc)
				throw ParseError("Missing value for '" + std::string(arg) + "'");
			++i;
		}

		switch (optionSpec->sence) {
		case options::Sense::Help:
			_help = true;
			return;
		case options::Sense::List:
			_list = true;
			return;
		case options::Sense::Quadratic:
			_quadratic = true;
			break;
		case options::Sense::Type:
			_type = std::string(argv[i]);
			break;
		case options::Sense::Size:
			_vectorSize = parseInt(argv[i]);
			break;
		case options::Sense::Gate:
			_gateSteps = parseInt(argv[i]);
			break;
		}
	}
}
