#pragma once

#include "sorts/SortingAlgorithm.hpp"

class QuickSortLomuto final : public SortingAlgorithm {
	std::shared_ptr<SyncingModel> _model;

	int partition(const int l, const int r) {
		auto pivot = _model->get(r);
		auto i = l - 1;
		for (auto j = l; j < r; ++j) {
			if (!_model->compare(_model->get(j), pivot)) continue;
			++i;
			_model->swap(i, j);
		}
		_model->swap(i + 1, r);
		return i + 1;
	}

	void quicksort(const int l, const int r) {
		if (l >= r) return;
		int i = partition(l, r);
		quicksort(l, i - 1);
		quicksort(i + 1, r);
	}

  public:
	const std::string_view name() override { return "QuickSort Lamuto"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		_model = std::move(model);
		quicksort(0, _model->size() - 1);
	}
};
