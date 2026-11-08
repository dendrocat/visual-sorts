#pragma once

#include <exception>

class SortCanceled : public std::exception {
  public:
	const char* what() const noexcept override { return "Sort cancelled"; }
};
