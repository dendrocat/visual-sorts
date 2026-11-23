#pragma once

#include "VisualType.hpp"

#include <cstddef>

struct Options {
	bool help;
	bool list;

	std::size_t vectorSize;
	std::size_t gateSteps;

	VisualType type;

	bool quadratic;
};
