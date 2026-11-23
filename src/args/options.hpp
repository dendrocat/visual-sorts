#pragma once

#include "VisualType.hpp"

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

inline constexpr std::size_t minVectorSize = 10;
inline constexpr std::size_t maxVectorSize = 50000;
inline constexpr std::size_t defaultVectorSize = 1000;

inline constexpr std::size_t minGateSteps = 1;
inline constexpr std::size_t maxGateSteps = 1000;
inline constexpr std::size_t defaultGateSteps = 5;

inline constexpr VisualType defaultType = VisualType::Bar;

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
