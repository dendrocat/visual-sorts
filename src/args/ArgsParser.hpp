#pragma once

#include <optional>
#include <string>

class ArgsParser final {

	bool _help = false;
	bool _list = false;

	std::optional<int>         _vectorSize;
	std::optional<int>         _gateSteps;
	std::optional<std::string> _type;
	std::optional<bool>        _quadratic;

	int parseInt(std::string_view sv);

  public:
	void parse(const int argc, const char* argv[]);

	bool help() const noexcept;
	bool list() const noexcept;

	const std::optional<int>&         vectorSize() const noexcept;
	const std::optional<int>&         gateSteps() const noexcept;
	const std::optional<std::string>& type() const noexcept;
	const std::optional<bool>&        quadratic() const noexcept;
};
