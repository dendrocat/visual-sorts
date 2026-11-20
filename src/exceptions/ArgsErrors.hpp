#pragma once

#include <stdexcept>
class ParseError : public std::runtime_error {
  public:
	explicit ParseError(std::string msg) : std::runtime_error("ParseError: " + msg) { }
};

class ValidationError : public std::runtime_error {
  public:
	explicit ValidationError(std::string msg)
		: std::runtime_error("ValidationError: " + msg) { }
};
