#pragma once

#include "macroses.hpp"

class Registry final {
	static void registerAlgorithms(bool quadratic);
	static void registerVisuals();

  public:
	NO_CREATE(Registry);

	static void init(bool quadratic);
};
