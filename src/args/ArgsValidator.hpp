#pragma once

#include "ArgsParser.hpp"
#include "visual.hpp"

#include <string>
#include <vector>

class ArgsValidator final {
	std::size_t _vectorSize;
	std::size_t _gateSteps;
	visual::ID  _visual;
	bool        _quadratic;

	std::vector<std::string> _errors;

	void validateVisual(const std::optional<std::string>& name);
	int  validateRange(const std::optional<int>& check, const int minValue,
					   const int maxValue, const int defaultValue,
					   const std::string_view name);

  public:
	void validate(const ArgsParser& parser);

	const std::vector<std::string>& errors() const noexcept;

	std::size_t vectorSize() const noexcept;
	std::size_t gateSteps() const noexcept;
	visual::ID  visual() const noexcept;
	bool        quadratic() const noexcept;
};
