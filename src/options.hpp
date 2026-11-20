#pragma once

#include "visual.hpp"

#include <optional>
#include <string>
#include <string_view>

namespace options
{
enum class Type { Flag, Value };
enum class Sense { Help, List, Type, Size, Gate, Quadratic };

struct OptionSpec {
	Type        type;
	const char* shortName;
	const char* longName;
	Sense       sense;

	std::string_view desc;
};

struct Options {
	std::optional<bool> help;
	std::optional<bool> list;

	std::optional<int>  vectorSize;
	std::optional<int> gateSteps;
	std::optional<bool> quadratic;

	std::optional<visual::Type> type;
	std::optional<std::string>  typeString;
};

inline constexpr int minVectorSize = 10;
inline constexpr int maxVectorSize = 50000;
inline constexpr int defaultVectorSize = 1000;

inline constexpr int minGateSteps = 1;
inline constexpr int maxGateSteps = 1000;
inline constexpr int defaultGateSteps = 5;

inline constexpr std::string_view defaultType = "bar";

inline constexpr bool defaultQuadratic = false;

inline constexpr OptionSpec specs[] = {
	{Type::Flag,  "-h",    "--help",      Sense::Help,      "Show this help"                       },
	{Type::Flag,  "-l",    "--list",      Sense::List,      "Show available visualisation types"   },

	{Type::Value, "-t",    "--type",      Sense::Type,      "Set visualisation type (default: bar)"},
	{Type::Value, "-s",    "--size",      Sense::Size,
	 "Set array size [10, 50000] (default: 1000)"                                                  },
	{Type::Value, "-g",    "--gate",      Sense::Gate,
	 "Set operations per frame [1, 1000] (default: 5)"                                             },
	{Type::Flag,  nullptr, "--quadratic", Sense::Quadratic,
	 "Enable quadtatic sorts (default: false)"                                                     },
};

inline const OptionSpec* findOption(std::string_view name) {
	for (const auto& spec : specs) {
		if (spec.shortName && name == spec.shortName) return &spec;
		if (spec.longName && name == spec.longName) return &spec;
	}
	return nullptr;
}
inline const OptionSpec* findOption(Sense sence) {
	for (const auto& spec : specs) {
		if (spec.sense == sence) return &spec;
	}
	return nullptr;
}

} // namespace options
