#include "VectorModel.hpp"

#include <algorithm>
#include <numeric>

VectorModel::VectorModel(std::size_t size) : _container(size), _markers(size, false) {
	std::ranges::iota(_container, 0);
}

std::size_t VectorModel::size() const noexcept { return _container.size(); }

int VectorModel::get(std::size_t i) const { return _container[i]; }

bool VectorModel::compare(const int& a, const int& b) noexcept {
	++_compares;
	return a < b;
}

void VectorModel::set(std::size_t i, int val) {
	_markers[i] = true;
	_container[i] = val;
	++_sets;
}

void VectorModel::swap(std::size_t i, std::size_t j) {
	_markers[i] = _markers[j] = true;
	std::swap(_container[i], _container[j]);
	++_swaps;
}

int VectorModel::compares() const { return _compares; }
int VectorModel::sets() const { return _sets; }
int VectorModel::swaps() const { return _swaps; }

bool VectorModel::markered(std::size_t i) const { return _markers[i]; }

void VectorModel::clearMarkers() { std::ranges::fill(_markers, false); }

void VectorModel::resetMeasures() { _compares = _sets = _swaps = 0; }
