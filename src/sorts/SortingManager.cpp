#include "SortingManager.hpp"
#include "exceptions/SortCanceled.hpp"
#include "AlgorithmFactory.hpp"

#include <cassert>
#include <functional>
#include <iostream>

SortingManager::SortingManager(std::shared_ptr<SyncingModel> model)
	: _model(std::move(model)) {
	_shuffler = std::make_unique<Shuffler>();
}

void SortingManager::start() {
	if (_thread) {
		return;
	}
	_thread = std::make_unique<std::jthread>(
		std::bind_front(&SortingManager::tryExecuteSorts, this));
}
void SortingManager::stop() {
	if (!_thread)
		return;
	_thread->request_stop();
}

void SortingManager::tryExecuteSorts(std::stop_token stoken) noexcept {
	_model->setStopToken(stoken);
	assert(stoken.stop_possible());
	try {
		executeSorts();
	}
#ifndef NDEBUG
	catch (const SortCanceled &e) {
		std::cerr << "\033[31m" << e.what() << "\033[0m\n";
	}
#else
	catch (const SortCanceled &) {
	}
#endif
	catch (const std::exception &e) {
		std::cerr << "Sort failed: " << e.what() << '\n';
	} catch (...) {
		std::cerr << "Sort failed with unknknown exception\n";
	}
}

void SortingManager::executeSorts() {
	std::size_t idx = 0;
	while (auto algo = AlgorithmFactory::instance().create(idx++)) {
		_shuffler->shuffle(_model);
		algo->sort(_model);
	}
}
