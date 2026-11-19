#pragma once

#include <string>
class ArgsParser final {
	static constexpr std::string_view visuals[] = {"bar", "ellipse"};

	static constexpr std::size_t      _defaultVectorSize = 1000;
	static constexpr std::size_t      _defaultGateSteps = 5;
	static constexpr std::string_view _defaultVisual = "bar";

	bool        _help = false;
	bool        _list = false;
	std::string _error = "";

	std::size_t      _vectorSize;
	std::size_t      _gateSteps;
	std::string_view _visual;

	bool checkVisual(std::string_view candidate) const noexcept;
	bool parseSizeT(std::string_view sv, std::size_t& out);
	void parse(const int argc, const char* argv[]);

	void printHelp() const noexcept;
	void printVisualList() const noexcept;

  public:
	ArgsParser(const int argc, const char* argv[]);

	bool help() const noexcept;
	bool error() const noexcept;

	std::string_view visual() const noexcept;
	std::size_t      vectorSize() const noexcept;
	std::size_t      gateSteps() const noexcept;
};
