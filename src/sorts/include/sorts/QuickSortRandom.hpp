#pragma once

#include "Random.hpp"
#include "sorts/SortingAlgorithm.hpp"

class QuickSortRandom final : public SortingAlgorithm {
	Random random;

	std::shared_ptr<SyncingModel> _model;

	int partition(const int l, const int r) {
		auto pivot = _model->get(random.get(l, r));
		int  i = l, j = r;
		while (1) {
			while (i <= r && _model->compare(_model->get(i), pivot)) ++i;
			while (j >= l && _model->compare(pivot, _model->get(j))) --j;
			if (i >= j) return j;
			_model->swap(i, j);
			++i, --j;
		}
	}

	void quicksort(const int l, const int r) {
		if (l >= r) return;
		int i = partition(l, r);
		quicksort(l, i);
		quicksort(i + 1, r);
	}

  public:
	const std::string_view name() override { return "QuickSort Random"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		_model = std::move(model);
		quicksort(0, _model->size() - 1);
	}
};
