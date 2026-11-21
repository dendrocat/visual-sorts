#pragma once

#include <string_view>

namespace visual
{
enum class Type { Bar, Ellipse };

struct VisualString {
	Type             type;
	std::string_view name;
};

inline constexpr VisualString visuals[] = {
	{Type::Bar,     "bar"    },
	{Type::Ellipse, "ellipse"},
};

constexpr std::string_view nameOf(Type type) {
	for (const auto& vs : visuals) {
		if (vs.type == type) {
			return vs.name;
		}
	}
	return {};
}

constexpr bool tryParseVisual(std::string_view s, Type& out) {
	for (const auto& vs : visuals) {
		if (vs.name == s) {
			out = vs.type;
			return true;
		}
	}
	return false;
}
}; // namespace visual
