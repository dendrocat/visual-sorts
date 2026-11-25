#pragma once

#define VISUAL_TYPES(X) \
	X(Bar)              \
	X(Ellipse)

namespace visual
{

enum class VisualType {
#define X(name) name,
	VISUAL_TYPES(X)
#undef X
};

} // namespace visual
