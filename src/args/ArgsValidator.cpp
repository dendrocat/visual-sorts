#include "ArgsValidator.hpp"

#include "exceptions/ArgsErrors.hpp"

visual::Type ArgsValidator::validateType(const std::optional<std::string>& visual) {
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
								 const std::string_view name) {
	if (!check.has_value()) return defaultValue;
	if (check.value() < minValue || check.value() > maxValue)
		throw ValidationError(std::string(name) + " must be in [" +
							  std::to_string(minValue) + ", " + std::to_string(maxValue) +
							  "]. Got: " + std::to_string(check.value()));
	return check.value();
}

void ArgsValidator::validate(options::Options& options) {
	options.help = options.help.value_or(false);
	options.list = options.list.value_or(false);

	options.type = validateType(options.typeString);

	options.vectorSize =
		validateRange(options.vectorSize, options::minVectorSize, options::maxVectorSize,
					  options::defaultVectorSize, "Array size");
	options.gateSteps =
		validateRange(options.gateSteps, options::minGateSteps, options::maxGateSteps,
					  options::defaultGateSteps, "Gate steps");

	options.quadratic = options.quadratic.value_or(false);
}
