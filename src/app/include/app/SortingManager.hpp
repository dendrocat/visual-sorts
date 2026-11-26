#pragma once

#include <memory>
#include <thread>

#include <Complexity.hpp>

#include <model/SyncingModel.hpp>

class SortingManager final {
  private:
	SyncingModel&   _model;

	std::unique_ptr<std::jthread> _thread;

	std::string _algorithmName;

	void tryExecuteSorts(std::stop_token stoken) noexcept;
	void executeSorts();

  public:
	NO_COPY_MOVE(SortingManager);

	SortingManager(SyncingModel& model, const sorts::Complexity quadratic);

	const std::string algorithmName();

	void start();
	void stop();
};
