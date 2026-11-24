#pragma once

#include <expected>
#include <string>

#include <macroses.hpp>

#include <Options.hpp>

class Args final {
  public:
	NO_CREATE(Args);

	static std::expected<Options, std::string> parse(const int argc, const char* argv[]);
};
