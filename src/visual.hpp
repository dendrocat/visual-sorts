#pragma once

#include <string_view>

namespace visual
{
enum class ID { Bar, Ellipse };

struct VisualString {
	ID               id;
	std::string_view name;
};

inline constexpr VisualString visuals[] = {
	{ID::Bar,     "bar"    },
	{ID::Ellipse, "ellipse"},
};

constexpr std::string_view nameOf(ID v) {
	for (const auto& vs : visuals)
		if (vs.id == v) return vs.name;
	return {};
}

constexpr bool tryParseVisual(std::string_view s, ID& out) {
	for (const auto& vs : visuals) {
		if (vs.name == s) {
			out = vs.id;
			return true;
		}
	}
	return false;
}
}; // namespace visual
