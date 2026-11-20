#pragma once

class Registry final {
	static void registerAlgorithms(bool quadratic);
	static void registerVisuals();

  public:
	static void init(bool quadratic);
};
