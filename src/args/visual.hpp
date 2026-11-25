#pragma once

#include <string_view>

#include <VisualType.hpp>

namespace visual
{

struct VisualString {
	visual::VisualType     type;
	std::string_view name;
};

inline constexpr VisualString visuals[] = {
#define X(name) {visual::VisualType::name, #name},
	VISUAL_TYPES(X)
#undef X
};

constexpr std::string_view nameOf(visual::VisualType type) {
	for (const auto& vs : visuals) {
		if (vs.type == type) {
			return vs.name;
		}
	}
	return {};
}

constexpr bool tryParseVisual(std::string_view s, visual::VisualType& out) {
	for (const auto& vs : visuals) {
		if (vs.name == s) {
			out = vs.type;
			return true;
		}
	}
	return false;
}

}; // namespace visual
