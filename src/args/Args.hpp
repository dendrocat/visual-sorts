#pragma once

#include "macroses.hpp"

#include "options.hpp"
#include "visual/visual.hpp"

#include <expected>
#include <string>

struct Error {
	const std::string message;
};

class Args final {
  private:
	options::Options _options;

	Args(options::Options options);

  public:
	MOVE_ONLY(Args);

	static std::expected<Args, Error> parse(const int argc, const char* argv[]);

	bool help() const noexcept;
	bool list() const noexcept;

	int vectorSize() const noexcept;
	int gateSteps() const noexcept;

	visual::Type type() const noexcept;

	bool quadratic() const noexcept;
};
