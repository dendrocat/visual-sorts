#include "ArgsValidator.hpp"

#include <args/ArgsErrors.hpp>

#include "options.hpp"

template <std::integral TNum>
void ArgsValidator::validateRange(const TNum& check, const TNum minValue,
								  const TNum maxValue, const std::string_view name) {
	if (check < minValue || check > maxValue)
		throw ValidationError(std::string(name) + " must be in [" +
							  std::to_string(minValue) + ", " + std::to_string(maxValue) +
							  "]. Got: " + std::to_string(check));
}

void ArgsValidator::validate(Options& options) {
	validateRange(options.vectorSize, options::minVectorSize, options::maxVectorSize,
				  "Array size");
	validateRange(options.gateSteps, options::minGateSteps, options::maxGateSteps,
				  "Gate steps");
}
