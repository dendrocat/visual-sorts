#pragma once

#include <concepts>
#include <random>

class Random {
  private:
	std::mt19937 rng;

  public:
	Random() : rng(std::random_device{}()) { }

	template <std::integral IntType = int>
	IntType get(IntType l, IntType r) {
		std::uniform_int_distribution<IntType> dist(l, r);
		return dist(rng);
	}

	template <std::floating_point RealType = float>
	RealType get(RealType l, RealType r) {
		std::uniform_real_distribution<RealType> dist(l, r);
		return dist(rng);
	}
};
