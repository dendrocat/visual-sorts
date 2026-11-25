#pragma once

#include <memory>
#include <thread>

#include <model/SyncingModel.hpp>

#include <sorts/Shuffler.hpp>

class SortingManager final {
  private:
	std::unique_ptr<Shuffler>     _shuffler;
	std::shared_ptr<SyncingModel> _model;

	std::unique_ptr<std::jthread> _thread;

	std::string _algorithmName;

	void tryExecuteSorts(std::stop_token stoken) noexcept;
	void executeSorts();

  public:
	NO_COPY_MOVE(SortingManager);

	SortingManager(std::shared_ptr<SyncingModel> model);

	const std::string algorithmName();

	void start();
	void stop();
};
