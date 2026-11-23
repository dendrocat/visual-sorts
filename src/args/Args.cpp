#include <Args.hpp>

#include "ArgsErrors.hpp"

#include "ArgsParser.hpp"
#include "ArgsValidator.hpp"

std::expected<Options, std::string> Args::parse(const int argc, const char* argv[]) {
	try {
		auto options = ArgsParser::parse(argc, argv);
		ArgsValidator::validate(options);
		return options;
	}
	catch (const ParseError& e) {
		return std::unexpected<std::string>{e.what()};
	}
	catch (const ValidationError& e) {
		return std::unexpected<std::string>{e.what()};
	}
}
