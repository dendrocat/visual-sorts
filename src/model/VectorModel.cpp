#include "VectorModel.hpp"

#include <numeric>

VectorModel::VectorModel(std::size_t size) : _container(size) {
	std::iota(_container.begin(), _container.end(), 0);
}

std::size_t VectorModel::size() const noexcept { return _container.size(); }

int VectorModel::get(std::size_t i) const { return _container[i]; }

void VectorModel::set(std::size_t i, int value) { _container[i] = value; }

void VectorModel::swap(std::size_t i, std::size_t j) {
	std::swap(_container[i], _container[j]);
}
