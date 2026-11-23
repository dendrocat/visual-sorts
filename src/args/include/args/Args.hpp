#pragma once

#include "macroses.hpp"

#include "Options.hpp"
#include "VisualType.hpp"

#include <expected>
#include <string>

class Args final {
  public:
	NO_CREATE(Args);

	static std::expected<Options, std::string> parse(const int argc, const char* argv[]);
};
