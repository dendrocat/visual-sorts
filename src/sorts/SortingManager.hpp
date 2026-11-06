#pragma once

#include "model/SyncingModel.hpp"
#include "Shuffler.hpp"

#include <memory>
#include <thread>

class SortingManager final {
  private:
	std::shared_ptr<SyncingModel> _model;
	std::unique_ptr<Shuffler> _shuffler;

	std::unique_ptr<std::jthread> _thread;

	void tryExecuteSorts(std::stop_token stoken) noexcept;
	void executeSorts();
	void shuffle();
	void executeSort();

  public:
	SortingManager(std::shared_ptr<SyncingModel> model);

	void start();

	void stop();
};
