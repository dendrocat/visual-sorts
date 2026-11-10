#pragma once

#include <stdexcept>

class SortCanceledException : public std::runtime_error {
  public:
	explicit SortCanceledException() : std::runtime_error("Sort cancelled") {}
};
