#include "ArgsParser.hpp"

#include "exceptions/ArgsErrors.hpp"
#include "options.hpp"

#include <charconv>
#include <string>
#include <utility>

bool ArgsParser::help() const noexcept { return _help.value_or(false); }
bool ArgsParser::list() const noexcept { return _list.value_or(false); }

const std::optional<int>& ArgsParser::vectorSize() const noexcept { return _vectorSize; }
const std::optional<int>& ArgsParser::gateSteps() const noexcept { return _gateSteps; }
const std::optional<std::string>& ArgsParser::type() const noexcept { return _type; }
const std::optional<bool>& ArgsParser::quadratic() const noexcept { return _quadratic; }

template <typename T>
void ArgsParser::setOnce(std::optional<T>& field, T&& value, std::string_view opt) {
	if (field.has_value())
		throw ParseError("Duplicated option '" + std::string(opt) + "'");
	field = std::forward<T>(value);
}

int ArgsParser::parseInt(std::string_view sv) {
	auto end = sv.data() + sv.size();
	int  res;
	auto [ptr, ec] = std::from_chars(sv.data(), end, res);

	if (ec == std::errc::invalid_argument)
		throw ParseError("Not a number: '" + std::string(sv) + "'");
	if (ec == std::errc::result_out_of_range)
		throw ParseError("Number out of range: '" + std::string(sv) + "'");
	if (ptr != end)
		throw ParseError("Trailing characters in number: '" + std::string(sv) + "'");
	return res;
}

void ArgsParser::parse(const int argc, const char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		const std::string_view arg = argv[i];

		auto optionSpec = options::findOption(arg);
		if (optionSpec == nullptr)
			throw ParseError("Unknown option '" + std::string(arg) + "'");

		if (optionSpec->type == options::Type::Value) {
			if (i + 1 >= argc || options::findOption(argv[i + 1]))
				throw ParseError("Missing value for '" + std::string(arg) + "'");
			++i;
		}

		switch (optionSpec->sense) {
		case options::Sense::Help:
			setOnce(_help, true, arg);
			_help = true;
			return;
		case options::Sense::List:
			setOnce(_list, true, arg);
			return;
		case options::Sense::Quadratic:
			setOnce(_quadratic, true, arg);
			break;
		case options::Sense::Type:
			setOnce(_type, std::string(argv[i]), arg);
			break;
		case options::Sense::Size:
			setOnce(_vectorSize, parseInt(argv[i]), arg);
			break;
		case options::Sense::Gate:
			setOnce(_gateSteps, parseInt(argv[i]), arg);
			break;
		}
	}
}
