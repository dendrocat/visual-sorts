#include <atomic>
#include <exception>
#include <functional>
#include <iostream>
#include <thread>

#include "model/SyncingModel.hpp"
#include "sorts/AlgorithmFactory.hpp"
#include "sorts/SortingAlgorithm.hpp"

namespace test
{
using Algo = sorts::SortingAlgorithm;

void driveWithoutVisuals(SyncingModel& model, const std::function<void()>& action) {
	std::atomic<bool>  done{ false };
	std::exception_ptr error;

	std::jthread worker([&] {
		try {
			action();
		}
		catch (...) {
			error = std::current_exception();
		}
		done.store(true, std::memory_order_release);
	});

	while (!done.load(std::memory_order_acquire)) {
		model.unlock();
		std::this_thread::yield();
	}

	worker.join();
	if (error) std::rethrow_exception(error);
}

bool isSorted(const VectorModel& model) {
	for (std::size_t i = 0; i < model.size(); ++i)
		if (model.get(i) != static_cast<int>(i)) return false;
	return true;
}

bool runCase(Algo& sorter, std::size_t size, const std::string_view& desc) {
	SyncingModel model{ size, 1 };

	auto s = sorts::AlgorithmFactory::instance().shuffler();

	driveWithoutVisuals(model, [&] {
		s->sort(model);
		sorter.sort(model);
	});

	if (isSorted(model.container())) {
		std::cout << "PASSED: " << desc << "\n";
		return true;
	}

	std::cerr << "FAILED: " << desc << ", size = " << size << "\n  got: ";
	for (std::size_t i = 0; i < model.size(); ++i) std::cerr << model.get(i) << ' ';
	std::cerr << '\n';
	return false;
}

int testOne(Algo& sorter) {
	int failures = 0;

	auto name = sorter.info().name;
	std::cout << name << " testing...\n";
	for (const auto size : { 2, 4, 5, 6, 10, 512, 1000 }) {
		std::string desc = std::to_string(size) + " elements";
		if (!test::runCase(sorter, size, desc)) {
			++failures;
			break;
		}
	}

	if (failures == 0) {
		std::cout << name << ": All tests passed\n";
		return 0;
	}

	std::cerr << name << ": " << failures << " test(s) failed\n";
	return 1;
}

} // namespace test

int main() {
	std::size_t idx = 0, passed = 0, failed = 0;
	while (auto sorter = sorts::AlgorithmFactory::instance().create(idx++)) {
		int res = test::testOne(*sorter);
		passed += 1 - res;
		failed += res;
	}
	std::cout << passed << " passed, " << failed << " failed\n";
}
