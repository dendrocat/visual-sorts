#pragma once

#include "ArgsParser.hpp"
#include "options.hpp"
#include "visual.hpp"

#include <concepts>
#include <string>

class ArgsValidator final {
	std::size_t  _vectorSize = options::defaultVectorSize;
	std::size_t  _gateSteps = options::defaultGateSteps;
	visual::Type _type = visual::Type::Bar;
	bool         _quadratic = options::defaultQuadratic;

	static visual::Type validateType(const std::optional<std::string>& name);

	template <std::integral In, std::integral Out>
	static Out validateRange(const std::optional<In>& check, const Out minValue,
							 const Out maxValue, const Out defaultValue,
							 const std::string_view name);

  public:
	MOVE_ONLY(ArgsValidator);

	void validate(const ArgsParser& parser);

	std::size_t  vectorSize() const noexcept;
	std::size_t  gateSteps() const noexcept;
	visual::Type type() const noexcept;
	bool         quadratic() const noexcept;
};
