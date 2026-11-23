#pragma once

#include <VisualType.hpp>

#include <string_view>

namespace visual
{

struct VisualString {
	VisualType       type;
	std::string_view name;
};

inline constexpr VisualString visuals[] = {
	{VisualType::Bar,     "bar"    },
	{VisualType::Ellipse, "ellipse"},
};

constexpr std::string_view nameOf(VisualType type) {
	for (const auto& vs : visuals) {
		if (vs.type == type) {
			return vs.name;
		}
	}
	return {};
}

constexpr bool tryParseVisual(std::string_view s, VisualType& out) {
	for (const auto& vs : visuals) {
		if (vs.name == s) {
			out = vs.type;
			return true;
		}
	}
	return false;
}

}; // namespace visual
