#include "sorts/SortingAlgorithm.hpp"

class MergeSort final : public SortingAlgorithm {
	std::shared_ptr<SyncingModel> _model;
	std::vector<int>              _left, _right;

	void merge(std::size_t l, std::size_t m, std::size_t r) {
		std::size_t size_l = m - l + 1, size_r = r - m;
		std::size_t i = 0, j = 0, k = l;

		for (; i < size_l; ++i, ++k) _left[i] = _model->get(k);
		for (; j < size_r; ++j, ++k) _right[j] = _model->get(k);

		i = 0, j = 0, k = l;
		while (i < size_l && j < size_r) {
			if (_model->compare(_left[i], _right[j])) {
				_model->set(k, _left[i]);
				++i;
			}
			else {
				_model->set(k, _right[j]);
				++j;
			}
			++k;
		}
		for (; i < size_l; ++i, ++k) _model->set(k, _left[i]);
		for (; j < size_r; ++j, ++k) _model->set(k, _right[j]);
	}

	void mergesort(std::size_t l, std::size_t r) {
		if (r - l < 1) return;
		auto m = (l + r) / 2;
		mergesort(l, m);
		mergesort(m + 1, r);
		merge(l, m, r);
	}

  public:
	const std::string_view name() override { return "Merge sort"; }

	void sort(std::shared_ptr<SyncingModel> model) override {
		_model = model;
		auto size = _model->size();
		_left.resize(size / 2 + 1);
		_right.resize(size / 2 + 1);
		mergesort(0, size - 1);
	}
};
