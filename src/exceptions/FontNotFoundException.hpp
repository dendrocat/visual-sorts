#pragma once

#include <stdexcept>

class FontNotFoundException : public std::runtime_error {
  public:
	explicit FontNotFoundException(const std::string& font)
		: std::runtime_error("Font not found: " + font) {}
};
