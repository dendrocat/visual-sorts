#pragma once

#include <macroses.hpp>

class Registry final {
	static void registerAlgorithms(bool quadratic);

  public:
	NO_CREATE(Registry);

	static void init(bool quadratic);
};
