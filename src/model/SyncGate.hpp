#pragma once

#include <condition_variable>
#include <mutex>
#include <stop_token>

class SyncGate final {
  private:
	std::mutex              _mutex;
	std::condition_variable_any _cv;
	std::stop_token         _stoken;

	const int _stepsBeforeWait = 5;
	int       _steps;

	bool _locked = false;

  public:
	SyncGate();
	SyncGate(const SyncGate&) = delete;
	SyncGate& operator=(const SyncGate&) = delete;

	void setStopToken(std::stop_token stoken) noexcept;

	void check();

	void unlock() noexcept;
	void lock() noexcept;
};
