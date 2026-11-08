#include "SyncingModel.hpp"

SyncingModel::SyncingModel(std::size_t size) : _model(size) {}

std::size_t SyncingModel::size() const noexcept { return _model.size(); }

int SyncingModel::get(std::size_t i) const { return _model.get(i); }

void SyncingModel::set(std::size_t i, int value) {
	_gate.check();
	_model.set(i, value);
}

void SyncingModel::swap(std::size_t i, std::size_t j) {
	_gate.check();
	_model.swap(i, j);
}

void SyncingModel::lock() { _gate.lock(); }
void SyncingModel::unlock() { _gate.unlock(); }

const VectorModel& SyncingModel::container() const noexcept { return _model; }

void SyncingModel::setStopToken(std::stop_token stoken) noexcept {
	_gate.setStopToken(stoken);
}
