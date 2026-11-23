#pragma once

#include "macroses.hpp"

class Usage final {
  public:
	NO_CREATE(Usage);

	static void help() noexcept;

	static void list() noexcept;
};
