#include "Usage.hpp"

#include "options.hpp"
#include "visual.hpp"

#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

void Usage::help() noexcept {
	constexpr std::size_t W = 28;

	auto left = [](const options::OptionSpec& spec) {
		std::string s;
		if (spec.shortName) s += spec.shortName;
		if (spec.shortName && spec.longName) s += ", ";
		if (spec.longName) s += spec.longName;
		return s;
	};
	auto row = [](std::string_view left, std::string_view right) {
		std::cout << "  " << std::left << std::setw(W) << left << right << "\n";
	};
	std::cout << "Usage: visual-sort\n";
	std::cout << "Options:\n";
	for (const auto& spec : options::specs) row(left(spec), spec.desc);

	std::cout << "\nExample:\n";
	std::cout << "  visual-sort ";
	auto type = options::findOption(options::Sense::Type);
	std::cout << std::format("{} {}", type->shortName,
							 visual::nameOf(options::defaultType))
			  << " ";
	auto size = options::findOption(options::Sense::Size);
	std::cout << size->shortName << " " << options::defaultVectorSize << " ";
	auto gate = options::findOption(options::Sense::Gate);
	std::cout << gate->shortName << " " << options::defaultGateSteps << "\n";
}

void Usage::list() noexcept {
	std::cout << "Available visualisation types:\n";
	for (const auto& vs : visual::visuals) {
		std::cout << "  " << vs.name << "\n";
	}
}
