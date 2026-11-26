#pragma once

namespace sorts
{

enum class Complexity : unsigned {
	None	= 0,
	Linear	= 1u << 0,
	NLogN	= 1u << 1,
	Quad	= 1u << 2,
	All		= Linear | NLogN | Quad
};

constexpr Complexity operator|(Complexity a, Complexity b) {
	return static_cast<Complexity>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
}

constexpr Complexity operator&(Complexity a, Complexity b) {
	return static_cast<Complexity>(static_cast<unsigned>(a) & static_cast<unsigned>(b));
}

constexpr Complexity operator~(Complexity a) {
	return static_cast<Complexity>(~static_cast<unsigned>(a));
}

constexpr Complexity& operator|=(Complexity& a, Complexity b) {
	a = a | b;
	return a;
}
constexpr Complexity& operator&=(Complexity& a, Complexity b) {
	a = a & b;
	return a;
}

}; // namespace sorts
