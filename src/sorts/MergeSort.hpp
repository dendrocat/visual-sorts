#pragma once

#include "sorts/SortingAlgorithm.hpp"

namespace sorts
{

class MergeSort final : public SortingAlgorithm {
	using vi = std::vector<int>;

	void merge(SyncingModel& model, vi& buf, std::size_t l, std::size_t m,
			   std::size_t r) const {
		std::size_t size_l = m - l + 1, size_r = r - m;
		std::size_t i = 0, j = 0, k = l;

		for (; i < size_l; ++i, ++k) buf[i] = model.get(k);
		for (; j < size_r; ++j, ++k) buf[size_l + j] = model.get(k);

		i = 0, j = 0, k = l;
		while (i < size_l && j < size_r) {
			if (model.compare(buf[j + size_l], buf[i])) {
				model.set(k, buf[j + size_l]);
				++j;
			}
			else {
				model.set(k, buf[i]);
				++i;
			}
			++k;
		}
		for (; i < size_l; ++i, ++k) model.set(k, buf[i]);
		for (; j < size_r; ++j, ++k) model.set(k, buf[j + size_l]);
	}

	void mergesort(SyncingModel& model, vi& buf, std::size_t l, std::size_t r) const {
		if (r - l < 1) return;
		std::size_t m = (l + r) / 2;
		mergesort(model, buf, l, m);
		mergesort(model, buf, m + 1, r);
		merge(model, buf, l, m, r);
	}

  public:
	[[nodiscard]] const AlgorithmInfo& info() const noexcept override {
		static AlgorithmInfo info{ .name = "Merge Sort",
								   .complexity = Complexity::NLogN };
		return info;
	}

	void sort(SyncingModel& model) const override {
		std::size_t size = model.size();

		std::vector<int> buf;
		buf.resize(size);
		mergesort(model, buf, 0, size - 1);
	}
};

}; // namespace sorts
