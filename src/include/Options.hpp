#pragma once

#include <cstddef>

#include "VisualType.hpp"

struct Options {
	bool help;
	bool list;

	std::size_t vectorSize;
	std::size_t gateSteps;

	visual::VisualType type;

	bool quadratic;
};
