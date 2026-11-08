#pragma once

#include <vector>

class VectorModel final {
  private:
	std::vector<int>  _container;
	std::vector<bool> _markers;

  public:
	VectorModel(std::size_t size);

	VectorModel(const VectorModel&) = delete;
	VectorModel& operator=(const VectorModel&) = delete;

	[[nodiscard]] std::size_t size() const noexcept;

	[[nodiscard]] int get(std::size_t i) const;

	bool compare(const int& a, const int& b) const noexcept;
	void set(std::size_t i, int val);
	void swap(std::size_t i, std::size_t j);

	[[nodiscard]] bool markered(std::size_t i) const;

	void clearMarkers();
};
