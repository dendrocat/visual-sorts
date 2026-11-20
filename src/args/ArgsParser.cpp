#include "ArgsParser.hpp"

#include "exceptions/ArgsErrors.hpp"

#include <charconv>
#include <iostream>
#include <string>
#include <utility>

template <typename T>
void ArgsParser::setOnce(std::optional<T>& field, T&& value, std::string_view opt) {
	if (field.has_value())
		throw ParseError("Duplicated option '" + std::string(opt) + "'");
	field = std::forward<T>(value);
}

visual::Type ArgsParser::parseType(std::string_view sv) {
	visual::Type type;
	if (!visual::tryParseVisual(sv, type))
		throw ParseError("Visual '" + std::string(sv) + "' doesn't supported");
	return type;
}

std::size_t ArgsParser::parseSizeT(std::string_view sv) {
	int res;
	auto [ptr, ec] = std::from_chars(sv.begin(), sv.end(), res);

	if (ec == std::errc::invalid_argument)
		throw ParseError("Not a number: '" + std::string(sv) + "'");
	if (ec == std::errc::result_out_of_range)
		throw ParseError("Number out of range: '" + std::string(sv) + "'");
	if (ptr != sv.end() || res < 0)
		throw ParseError("Trailing characters in number: '" + std::string(sv) + "'");
	return static_cast<std::size_t>(res);
}

options::Options ArgsParser::parse(const int argc, const char* argv[]) {
	options::Options options;
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

		switch (optionSpec->sense) {
		case options::Sense::Help:
			setOnce(options.help, true, arg);
			break;
		case options::Sense::List:
			setOnce(options.list, true, arg);
			break;
		case options::Sense::Quadratic:
			setOnce(options.quadratic, true, arg);
			break;
		case options::Sense::Type:
			setOnce(options.type, parseType(argv[i]), arg);
			break;
		case options::Sense::Size:
			setOnce(options.vectorSize, parseSizeT(argv[i]), arg);
			break;
		case options::Sense::Gate:
			setOnce(options.gateSteps, parseSizeT(argv[i]), arg);
			break;
		}
		if (options.help || options.list) break;
	}
	return options;
}
