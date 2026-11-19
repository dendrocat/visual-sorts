#pragma once

#include "ArgsParser.hpp"
#include "ArgsValidator.hpp"
#include "visual.hpp"

class Args final {
  private:
	ArgsParser    _parser;
	ArgsValidator _validator;

	std::vector<std::string> _errors;

  public:
	Args(const int argc, const char* argv[]);

	const std::vector<std::string>& errors() const noexcept;

	std::size_t vectorSize() const noexcept;
	std::size_t gateSteps() const noexcept;
	visual::ID  visual() const noexcept;
	bool        quadratic() const noexcept;

	bool help() const noexcept;
	bool list() const noexcept;

	static void printHelp();
	static void printList();
};
