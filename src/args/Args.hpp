#pragma once

#include "ArgsParser.hpp"
#include "ArgsValidator.hpp"
#include "visual.hpp"

#include <expected>
#include <string>

struct ArgsError {
	const std::string error;
};

class Args final {
  private:
	ArgsParser    _parser;
	ArgsValidator _validator;

	Args(const int argc, const char* argv[]);

  public:
	static std::expected<Args, ArgsError> parse(const int argc, const char* argv[]);

	std::size_t  vectorSize() const noexcept;
	std::size_t  gateSteps() const noexcept;
	visual::Type type() const noexcept;
	bool         quadratic() const noexcept;

	bool help() const noexcept;
	bool list() const noexcept;
};
