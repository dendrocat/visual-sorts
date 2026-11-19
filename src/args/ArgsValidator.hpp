#pragma once

#include "ArgsParser.hpp"
#include "visual.hpp"

#include <string>

class ArgsValidator final {
	std::size_t  _vectorSize;
	std::size_t  _gateSteps;
	visual::Type _type;
	bool         _quadratic;

	visual::Type validateType(const std::optional<std::string>& name) const;
	int          validateRange(const std::optional<int>& check, const int minValue,
							   const int maxValue, const int defaultValue,
							   const std::string_view name) const;

  public:
	void validate(const ArgsParser& parser);

	std::size_t  vectorSize() const noexcept;
	std::size_t  gateSteps() const noexcept;
	visual::Type type() const noexcept;
	bool         quadratic() const noexcept;
};
