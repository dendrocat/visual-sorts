#pragma once

#include "macroses.hpp"

#include <optional>
#include <string>
#include <string_view>

class ArgsParser final {

	std::optional<bool> _help;
	std::optional<bool> _list;

	std::optional<int>         _vectorSize;
	std::optional<int>         _gateSteps;
	std::optional<std::string> _type;
	std::optional<bool>        _quadratic;

	template <typename T>
	static void setOnce(std::optional<T>& field, T&& value, std::string_view opt);
	static int  parseInt(std::string_view sv);

  public:
	MOVE_ONLY(ArgsParser);

	void parse(const int argc, const char* argv[]);

	bool help() const noexcept;
	bool list() const noexcept;

	const std::optional<int>&         vectorSize() const noexcept;
	const std::optional<int>&         gateSteps() const noexcept;
	const std::optional<std::string>& type() const noexcept;
	const std::optional<bool>&        quadratic() const noexcept;
};
