#pragma once

#include "macroses.hpp"

#include "options.hpp"
#include "visual.hpp"

#include <concepts>
#include <string>
#include <string_view>

class ArgsValidator final {
	static visual::Type validateType(const std::optional<std::string>& name);

	template <std::integral TNum>
	static TNum validateRange(const std::optional<TNum>& check, const TNum minValue,
							 const TNum maxValue, const TNum defaultValue,
							 const std::string_view name);

  public:
	NO_CREATE(ArgsValidator);

	static void validate(options::Options& options);
};
