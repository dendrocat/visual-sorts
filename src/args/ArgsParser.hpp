#pragma once

#include <string_view>

#include <macroses.hpp>

#include <Options.hpp>
#include <VisualType.hpp>

class ArgsParser final {
	static Options getDefaults();

	static visual::VisualType parseType(std::string_view sv);
	static std::size_t  parseSizeT(std::string_view sv);

  public:
	NO_CREATE(ArgsParser);

	[[nodiscard]] static Options parse(const int argc, const char* argv[]);
};
