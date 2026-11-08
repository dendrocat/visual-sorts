#include "SyncGate.hpp"
#include "exceptions/SortCanceled.hpp"

SyncGate::SyncGate() : _steps(_stepsBeforeWait) {}

void SyncGate::setStopToken(std::stop_token stoken) noexcept {
	{
		std::unique_lock lk(_mutex);
		_stoken = stoken;
	}
	_cv.notify_all();
}

void SyncGate::check() {
	{
		std::unique_lock lk(_mutex);
		_cv.wait(lk, [this] { return !_locked && _steps > 0; });
		if (_stoken.stop_requested()) throw SortCanceled{};
	}
	--_steps;
}

void SyncGate::unlock() noexcept {
	{
		std::lock_guard lk(_mutex);
		_locked = false;
		_steps = _stepsBeforeWait;
	}
	_cv.notify_all();
}

void SyncGate::lock() noexcept {
	{
		std::lock_guard lk(_mutex);
		_locked = true;
	}
	_cv.notify_all();
}
