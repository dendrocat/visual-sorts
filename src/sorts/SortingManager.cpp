#include "SortingManager.hpp"
#include "AlgorithmFactory.hpp"
#include "exceptions/SortCanceledException.hpp"

#include <cassert>
#include <functional>
#include <iostream>

SortingManager::SortingManager(std::shared_ptr<SyncingModel> model)
	: _model(std::move(model)) {
	_shuffler = std::make_unique<Shuffler>();
}

bool SortingManager::isSorting() { return _isSorting; }
const std::string SortingManager::algorithmName() { return _algorithmName; }

void SortingManager::start() {
	if (_thread) return;
	_thread = std::make_unique<std::jthread>(
		std::bind_front(&SortingManager::tryExecuteSorts, this));
}

void SortingManager::stop() {
	if (!_thread) return;
	_thread->request_stop();
}

void SortingManager::tryExecuteSorts(std::stop_token stoken) noexcept {
	_model->setStopToken(stoken);
	assert(stoken.stop_possible());
	try {
		executeSorts();
	}
#ifndef NDEBUG
	catch (const SortCanceledException& e) {
		std::cerr << "\033[31m" << e.what() << "\033[0m\n";
	}
#else
	catch (const SortCanceledException&) {
	}
#endif
	catch (const std::exception& e) {
		std::cerr << "Sort failed: " << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Sort failed with unknknown exception\n";
	}
}

void SortingManager::executeSorts() {
	std::size_t idx = 0;
	while (auto algo = AlgorithmFactory::instance().create(idx++)) {
		_isSorting = false;
		_model->resetMeasures();
		_algorithmName = _shuffler->name();
		_shuffler->sort(_model);

		_isSorting = true;
		_model->resetMeasures();
		_algorithmName = algo->name();
		algo->sort(_model);
	}
}
