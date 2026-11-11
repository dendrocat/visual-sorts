#include "SyncGate.hpp"
#include "exceptions/SortCanceledException.hpp"

SyncGate::SyncGate(std::size_t maxSteps) : _maxSteps(maxSteps), _steps(maxSteps) { }

void SyncGate::setStopToken(std::stop_token stoken) noexcept {
	{
		std::unique_lock lk(_mutex);
		_stoken = stoken;
	}
	_cv.notify_all();
}

void SyncGate::check() {
	std::unique_lock lk(_mutex);
	_cv.wait(lk, _stoken, [this] { return !_locked && _steps > 0; });
	if (_stoken.stop_requested()) throw SortCanceledException{};
	--_steps;
}

void SyncGate::unlock() noexcept {
	{
		std::lock_guard lk(_mutex);
		_locked = false;
		_steps = _maxSteps;
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
