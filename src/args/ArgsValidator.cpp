#include "ArgsValidator.hpp"

#include "exceptions/ArgsErrors.hpp"
#include "options.hpp"

#include <string_view>

visual::Type ArgsValidator::validateType(const std::optional<std::string>& visual) const {
	visual::Type type;

	auto visualName = options::defaultType;
	if (visual.has_value()) visualName = visual.value();

	if (!visual::tryParseVisual(visualName, type))
		throw ValidationError("Visual '" + std::string(visualName) +
							  "' doesn't supported");
	return type;
}

int ArgsValidator::validateRange(const std::optional<int>& check, const int minValue,
								 const int maxValue, const int defaultValue,
								 const std::string_view name) const {
	if (!check.has_value()) return defaultValue;
	if (check.value() < minValue || check.value() > maxValue) {
		throw ValidationError(std::string(name) + " must be in [" +
							  std::to_string(minValue) + ", " + std::to_string(maxValue) +
							  "]. Got: " + std::to_string(check.value()));
		return defaultValue;
	}
	return check.value();
}

void ArgsValidator::validate(const ArgsParser& parser) {
	_type = validateType(parser.type());
	_vectorSize =
		validateRange(parser.vectorSize(), options::minVectorSize, options::maxVectorSize,
					  options::defaultVectorSize, "Vector size");
	_gateSteps =
		validateRange(parser.gateSteps(), options::minGateSteps, options::maxGateSteps,
					  options::defaultGateSteps, "Gate steps");
	_quadratic = parser.quadratic().value_or(options::quadratic);
}

std::size_t  ArgsValidator::vectorSize() const noexcept { return _vectorSize; }
std::size_t  ArgsValidator::gateSteps() const noexcept { return _gateSteps; }
visual::Type ArgsValidator::type() const noexcept { return _type; }
bool         ArgsValidator::quadratic() const noexcept { return _quadratic; }
