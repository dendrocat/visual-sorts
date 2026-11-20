#pragma once

#include <string_view>

namespace visual
{
enum class Type { Bar, Ellipse };

struct VisualString {
	Type             id;
	std::string_view name;
};

inline constexpr VisualString visuals[] = {
	{Type::Bar,     "bar"    },
	{Type::Ellipse, "ellipse"},
};

constexpr bool tryParseVisual(std::string_view s, Type& out) {
	for (const auto& vs : visuals) {
		if (vs.name == s) {
			out = vs.id;
			return true;
		}
	}
	return false;
}
}; // namespace visual
