#pragma once

#include "sorts/SortingAlgorithm.hpp"
#include <memory>

class QuickSortDualPivot final : public SortingAlgorithm {
	std::shared_ptr<SyncingModel> _model;

	std::pair<int, int> partition(const int l, const int r) {
		if (_model->compare(_model->get(r), _model->get(l)))
			_model->swap(l, r);
		auto less_pivot1 = l + 1, greater_pivot2 = r - 1;
		auto i = less_pivot1;
		auto p1 = _model->get(l), p2 = _model->get(r);
		while (i <= greater_pivot2) {
			if (_model->compare(_model->get(i), p1)) {
				_model->swap(i, less_pivot1);
				++less_pivot1;
			}
			else if (_model->compare(p2, _model->get(i))) {
				_model->swap(greater_pivot2, i);
				--greater_pivot2;
				--i;
			}
			++i;
		}
		--less_pivot1, ++greater_pivot2;
		_model->swap(less_pivot1, l);
		_model->swap(greater_pivot2, r);
		return {less_pivot1, greater_pivot2};
	}

	void quicksort(const int l, const int r) {
		if (l >= r) return;
		auto p = partition(l, r);
		quicksort(l, p.first - 1);
		quicksort(p.first + 1, p.second - 1);
		quicksort(p.second + 1, r);
	}

  public:
	const std::string_view name() override { return "QuickSort Dual pivot"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		_model = std::move(model);
		quicksort(0, _model->size() - 1);
	}
};
