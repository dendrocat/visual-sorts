#include "ArgsValidator.hpp"

#include "defaults.hpp"
#include "exceptions/ArgsErrors.hpp"
#include <string_view>

void ArgsValidator::validateType(const std::optional<std::string>& visual) {
	auto visualName = defaults::visual;
	if (visual.has_value()) visualName = visual.value();

	if (!visual::tryParseVisual(visualName, _type))
		throw ValidationError("Visual '" + std::string(visualName) +
							  "' doesn't supported");
}

int ArgsValidator::validateRange(const std::optional<int>& check, const int minValue,
								 const int maxValue, const int defaultValue,
								 const std::string_view name) {
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
	validateType(parser.type());
	_vectorSize =
		validateRange(parser.vectorSize(), defaults::minVectorSize,
					  defaults::maxVectorSize, defaults::vectorSize, "Vector size");
	_gateSteps = validateRange(parser.gateSteps(), defaults::minGateSteps,
							   defaults::maxGateSteps, defaults::gateSteps, "Gate steps");
	_quadratic = parser.quadratic().value_or(defaults::quadratic);
}

std::size_t  ArgsValidator::vectorSize() const noexcept { return _vectorSize; }
std::size_t  ArgsValidator::gateSteps() const noexcept { return _gateSteps; }
visual::Type ArgsValidator::type() const noexcept { return _type; }
bool         ArgsValidator::quadratic() const noexcept { return _quadratic; }
