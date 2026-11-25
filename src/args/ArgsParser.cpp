#include "ArgsParser.hpp"

#include <args/ArgsErrors.hpp>

#include "options.hpp"
#include "visual.hpp"

#include <charconv>
#include <string>
#include <unordered_set>

Options ArgsParser::getDefaults() {
	return Options{.help = false,
				   .list = false,
				   .vectorSize = options::defaultVectorSize,
				   .gateSteps = options::defaultGateSteps,
				   .type = options::defaultType,
				   .quadratic = options::defaultQuadratic};
}

visual::VisualType ArgsParser::parseType(std::string_view sv) {
	visual::VisualType type;
	if (!visual::tryParseVisual(sv, type))
		throw ParseError("Visual '" + std::string(sv) + "' doesn't supported");
	return type;
}

std::size_t ArgsParser::parseSizeT(std::string_view sv) {
	std::size_t res;
	auto [ptr, ec] = std::from_chars(sv.begin(), sv.end(), res);

	if (ec == std::errc::invalid_argument)
		throw ParseError("Not a number: '" + std::string(sv) + "'");
	if (ec == std::errc::result_out_of_range)
		throw ParseError("Number out of range: '" + std::string(sv) + "'");
	if (ptr != sv.end())
		throw ParseError("Trailing characters in number: '" + std::string(sv) + "'");
	return res;
}

Options ArgsParser::parse(const int argc, const char* argv[]) {
	Options options = getDefaults();

	std::unordered_set<options::Sense> was;
	auto once = [&was](const options::Sense& sense, const std::string_view sv) {
		if (was.contains(sense))
			throw ParseError("Duplicated option: '" + std::string(sv) + "'");
		was.insert(sense);
	};

	for (int i = 1; i < argc; ++i) {
		const std::string_view arg = argv[i];

		auto optionSpec = options::findOption(arg);
		if (optionSpec == nullptr)
			throw ParseError("Unknown option '" + std::string(arg) + "'");

		if (optionSpec->type == options::Type::Value) {
			if (i + 1 >= argc || options::findOption(argv[i + 1]))
				throw ParseError("Missing value for '" + std::string(arg) + "'");
			++i;
		}

		once(optionSpec->sense, arg);

		switch (optionSpec->sense) {
		case options::Sense::Help:
			options.help = true;
			break;
		case options::Sense::List:
			options.list = true;
			break;
		case options::Sense::Quadratic:
			options.quadratic = true;
			break;
		case options::Sense::Type:
			options.type = parseType(argv[i]);
			break;
		case options::Sense::Size:
			options.vectorSize = parseSizeT(argv[i]);
			break;
		case options::Sense::Gate:
			options.gateSteps = parseSizeT(argv[i]);
			break;
		}
		if (options.help || options.list) break;
	}
	return options;
}
