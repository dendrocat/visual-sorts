#pragma once

#include <macroses.hpp>

#include <model/SyncGate.hpp>
#include <model/VectorModel.hpp>

#include <cstddef>
#include <stop_token>

class SyncingModel final {
  private:
	VectorModel _model;
	SyncGate    _gate;

  public:
	NO_COPY_MOVE(SyncingModel);

	SyncingModel(const std::size_t size, const std::size_t gateSteps);

	[[nodiscard]] std::size_t size() const noexcept;

	[[nodiscard]] int get(std::size_t i) const;

	bool compare(const int& a, const int& b);
	void set(std::size_t i, int value);
	void swap(std::size_t i, std::size_t j);

	[[nodiscard]] const VectorModel& container() const noexcept;

	void clearMarkers();

	void resetMeasures();

	void setStopToken(std::stop_token stoken) noexcept;

	void lock();
	void unlock();
};
