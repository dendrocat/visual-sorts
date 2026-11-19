#pragma once

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
	Sense       sence;

	const std::string desc;
};

inline constexpr std::size_t minVectorSize = 10;
inline constexpr std::size_t maxVectorSize = 100000;
inline constexpr std::size_t defaultVectorSize = 1000;

inline constexpr std::size_t minGateSteps = 1;
inline constexpr std::size_t maxGateSteps = 1000;
inline constexpr std::size_t defaultGateSteps = 5;

inline constexpr std::string_view defaultType = "bar";
inline constexpr bool             quadratic = false;

inline const OptionSpec specs[] = {
	{Type::Flag,  "-h", "--help",      Sense::Help,      "Show this help"               },
	{Type::Flag,  "-l", "--list",      Sense::List,      "Show available visualisations"},

	{Type::Value, "-t", "--type",      Sense::Type,
	 "Set visualisation type (default: " + std::string(defaultType) + ")"             },
	{Type::Value, "-s", "--size",      Sense::Size,
	 "Set array size [" + std::to_string(minVectorSize) + ", " +
		 std::to_string(maxVectorSize) +
		 "] (default: " + std::to_string(defaultVectorSize) + ")"                       },
	{Type::Value, "-g", "--gate",      Sense::Gate,
	 "Set array size [" + std::to_string(minGateSteps) + ", " +
		 std::to_string(maxGateSteps) +
		 "] (default: " + std::to_string(defaultGateSteps) + ")"                        },
	{Type::Flag,  nullptr,   "--quadratic", Sense::Quadratic,
	 "Enalbe quadtatic sorts (default: " + std::to_string(quadratic) + ")"              },
};


inline const OptionSpec* findOption(std::string_view name) {
	for (const auto& spec : specs) {
		if (spec.shortName && spec.shortName == name) return &spec;
		if (spec.longName && spec.longName == name) return &spec;
	}
	return nullptr;
}
inline const OptionSpec* findOption(Sense sence) {
	for (const auto& spec : specs) {
		if (spec.sence == sence) return &spec;
	}
	return nullptr;
}

} // namespace options
