#pragma once

#include "macroses.hpp"

#include "Options.hpp"

#include <concepts>
#include <string_view>

class ArgsValidator final {
	template <std::integral TNum>
	static void validateRange(const TNum& check, const TNum minValue, const TNum maxValue,
							  const std::string_view name);

  public:
	NO_CREATE(ArgsValidator);

	static void validate(Options& options);
};
