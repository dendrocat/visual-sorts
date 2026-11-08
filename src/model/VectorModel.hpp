#pragma once

#include <vector>

class VectorModel final {
  private:
	std::vector<int> _container;

  public:
	VectorModel(std::size_t size);

	VectorModel(const VectorModel&) = delete;
	VectorModel& operator=(const VectorModel&) = delete;

	[[nodiscard]] std::size_t size() const noexcept;

	[[nodiscard]] int get(std::size_t i) const;

	void set(std::size_t i, int value);

	void swap(std::size_t i, std::size_t j);
};
