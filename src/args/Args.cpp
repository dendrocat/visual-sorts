#include "Args.hpp"

#include "exceptions/ArgsErrors.hpp"

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
		return std::unexpected<ArgsError>{e.what()};
	}
	catch (const ValidationError& e) {
		return std::unexpected<ArgsError>{e.what()};
	}
}

std::size_t  Args::vectorSize() const noexcept { return _validator.vectorSize(); }
std::size_t  Args::gateSteps() const noexcept { return _validator.gateSteps(); }
visual::Type Args::type() const noexcept { return _validator.type(); }
bool         Args::quadratic() const noexcept { return _validator.quadratic(); }

bool Args::help() const noexcept { return _parser.help(); }
bool Args::list() const noexcept { return _parser.list(); }
