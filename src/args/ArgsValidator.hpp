#pragma once

#include "macroses.hpp"

#include "options.hpp"
#include "visual.hpp"

#include <string>
#include <string_view>

class ArgsValidator final {
	static visual::Type validateType(const std::optional<std::string>& name);

	static int validateRange(const std::optional<int>& check, const int minValue,
							 const int maxValue, const int defaultValue,
							 const std::string_view name);

  public:
	NO_CREATE(ArgsValidator);

	static void validate(options::Options& options);
};
