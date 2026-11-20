#pragma once

#include "macroses.hpp"

#include "options.hpp"

#include <optional>
#include <string_view>

class ArgsParser final {
	template <typename T>
	static void setOnce(std::optional<T>& field, T&& value, std::string_view opt);
	static int  parseInt(std::string_view sv);

  public:
	NO_CREATE(ArgsParser);

	[[nodiscard]] static options::Options parse(const int argc, const char* argv[]);
};
