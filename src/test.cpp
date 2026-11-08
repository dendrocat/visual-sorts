#include "model/SyncingModel.hpp"
#include "sorts/MergeSort.hpp"
#include "sorts/Shuffler.hpp"

#include <atomic>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

namespace test
{
using Sorter = MergeSort;

void driveWithoutVisuals(SyncingModel& model, const std::function<void()>& action) {
	std::atomic<bool>  done{false};
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
		model.gate().unlock();
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

bool runCase(std::size_t size, const std::string_view& desc) {
	auto model = std::make_shared<SyncingModel>(size);

	Shuffler s;
	Sorter   sorter;

	driveWithoutVisuals(*model, [&] {
		s.shuffle(model);
		sorter.sort(model);
	});

	if (isSorted(model->container())) {
		std::cout << "PASSED: " << desc << "\n";
		return true;
	}

	std::cerr << "FAILED: " << desc << ", size = " << size << "\n  got: ";
	for (std::size_t i = 0; i < model->size(); ++i) std::cerr << model->get(i) << ' ';
	std::cerr << '\n';
	return false;
}

} // namespace tmp

int main() {
	int failures = 0;

	for (const auto size : {2, 4, 5, 6, 10, 512, 1000}) {
		std::string desc = std::to_string(size) + " elements";
		failures += !test::runCase(size, desc);
	}

	std::string name;
	{
		test::Sorter s;
		name = s.name();
	}
	if (failures == 0) {
		std::cout << name <<  ": All tests passed\n";
		return 0;
	}

	std::cerr << name << ": " << failures << " test(s) failed\n";
	return 1;
}
