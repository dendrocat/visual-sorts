#pragma once

#include "macroses.hpp"

#include <condition_variable>
#include <mutex>
#include <stop_token>

class SyncGate final {
  private:
	std::mutex                  _mutex;
	std::condition_variable_any _cv;
	std::stop_token             _stoken;

	int _maxSteps, _steps;

	bool _locked = false;

  public:
	NO_COPY_MOVE(SyncGate);

	SyncGate(std::size_t maxSteps);

	void setStopToken(std::stop_token stoken) noexcept;

	void check();

	void unlock() noexcept;
	void lock() noexcept;
};
