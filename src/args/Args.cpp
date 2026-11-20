#include "Args.hpp"

#include "args/ArgsParser.hpp"
#include "args/ArgsValidator.hpp"
#include "exceptions/ArgsErrors.hpp"

Args::Args(options::Options options) : _options(std::move(options)) { }

std::expected<Args, Error> Args::parse(const int argc, const char* argv[]) {
	try {
		auto options = ArgsParser::parse(argc, argv);
		ArgsValidator::validate(options);
		return Args{std::move(options)};
	}
	catch (const ParseError& e) {
		return std::unexpected<Error>{e.what()};
	}
	catch (const ValidationError& e) {
		return std::unexpected<Error>{e.what()};
	}
}

bool Args::help() const noexcept { return _options.help.value(); }
bool Args::list() const noexcept { return _options.list.value(); }

int Args::vectorSize() const noexcept { return _options.vectorSize.value(); }
int Args::gateSteps() const noexcept { return _options.gateSteps.value(); }

visual::Type Args::type() const noexcept { return _options.type.value(); }

bool Args::quadratic() const noexcept { return _options.quadratic.value(); }
