#pragma once

#include "SyncGate.hpp"
#include "VectorModel.hpp"

class SyncingModel final {
  private:
	SyncGate _gate;
	VectorModel _model;

  public:
	SyncingModel(std::size_t size);

	SyncingModel(const VectorModel &) = delete;
	SyncingModel &operator=(const VectorModel &) = delete;

	[[nodiscard]] std::size_t size() const noexcept;

	[[nodiscard]] int get(std::size_t i) const;
	void set(std::size_t i, int value);

	void swap(std::size_t i, std::size_t j);

	void lock();
	void unlock();

	[[nodiscard]] const VectorModel &container() const noexcept;
	void setStopToken(std::stop_token stoken) noexcept;
};
