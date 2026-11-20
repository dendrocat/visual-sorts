#include "ArgsValidator.hpp"

#include "exceptions/ArgsErrors.hpp"
#include "options.hpp"

#include <string_view>
#include <utility>

visual::Type ArgsValidator::validateType(const std::optional<std::string>& visual) {
	visual::Type type;

	auto visualName = options::defaultType;
	if (visual.has_value()) visualName = visual.value();

	if (!visual::tryParseVisual(visualName, type))
		throw ValidationError("Visual '" + std::string(visualName) +
							  "' doesn't supported");
	return type;
}

template <std::integral In, std::integral Out>
Out ArgsValidator::validateRange(const std::optional<In>& check, const Out minValue,
								 const Out maxValue, const Out defaultValue,
								 const std::string_view name) {
	if (!check.has_value()) return defaultValue;
	if (std::cmp_less(check.value(), minValue) ||
		std::cmp_greater(check.value(), maxValue))
		throw ValidationError(std::string(name) + " must be in [" +
							  std::to_string(minValue) + ", " + std::to_string(maxValue) +
							  "]. Got: " + std::to_string(check.value()));
	return check.value();
}

void ArgsValidator::validate(const ArgsParser& parser) {
	_type = validateType(parser.type());
	_vectorSize =
		validateRange(parser.vectorSize(), options::minVectorSize, options::maxVectorSize,
					  options::defaultVectorSize, "Array size");
	_gateSteps =
		validateRange(parser.gateSteps(), options::minGateSteps, options::maxGateSteps,
					  options::defaultGateSteps, "Gate steps");
	_quadratic = parser.quadratic().value_or(options::defaultQuadratic);
}

std::size_t  ArgsValidator::vectorSize() const noexcept { return _vectorSize; }
std::size_t  ArgsValidator::gateSteps() const noexcept { return _gateSteps; }
visual::Type ArgsValidator::type() const noexcept { return _type; }
bool         ArgsValidator::quadratic() const noexcept { return _quadratic; }
