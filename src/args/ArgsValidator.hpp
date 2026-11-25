#pragma once

#include <concepts>
#include <string_view>

#include <macroses.hpp>

#include <Options.hpp>

class ArgsValidator final {
	template <std::integral TNum>
	static void validateRange(const TNum& check, const TNum minValue, const TNum maxValue,
							  const std::string_view name);

  public:
	NO_CREATE(ArgsValidator);

	static void validate(Options& options);
};
