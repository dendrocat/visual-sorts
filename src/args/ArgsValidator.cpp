#include "ArgsValidator.hpp"

#include "exceptions/ArgsErrors.hpp"

template <std::integral TNum>
TNum ArgsValidator::validateRange(const std::optional<TNum>& check, const TNum minValue,
								  const TNum maxValue, const TNum defaultValue,
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

	options.type = options.type.value_or(options::defaultType);

	options.vectorSize =
		validateRange(options.vectorSize, options::minVectorSize, options::maxVectorSize,
					  options::defaultVectorSize, "Array size");
	options.gateSteps =
		validateRange(options.gateSteps, options::minGateSteps, options::maxGateSteps,
					  options::defaultGateSteps, "Gate steps");

	options.quadratic = options.quadratic.value_or(options::defaultQuadratic);
}
