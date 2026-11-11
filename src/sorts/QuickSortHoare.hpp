#pragma once

#include "sorts/SortingAlgorithm.hpp"

class QuickSortHoare final : public SortingAlgorithm {
	std::shared_ptr<SyncingModel> _model;

	int partition(const std::size_t l, const std::size_t r) {
		int i = l, j = r;
		int pivot = _model->get((l + r) / 2);
		while (1) {
			while (_model->compare(_model->get(i), pivot)) ++i;
			while (_model->compare(pivot, _model->get(j))) --j;
			if (i >= j) return j;
			_model->swap(i, j);
			++i;
			--j;
		}
	}

	void quicksort(const std::size_t l, const std::size_t r) {
		if (l >= r) return;
		int i = partition(l, r);
		quicksort(l, i);
		quicksort(i + 1, r);
	}

  public:
	const std::string_view name() override { return "QuickSort Hoare"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		_model = std::move(model);
		quicksort(0, _model->size() - 1);
	}
};
