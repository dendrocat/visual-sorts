#pragma once

#include <cstddef>
#include <string_view>

namespace defaults
{

inline constexpr std::size_t minVectorSize = 10;
inline constexpr std::size_t maxVectorSize = 100000;
inline constexpr std::size_t vectorSize = 1000;

inline constexpr std::size_t minGateSteps = 1;
inline constexpr std::size_t maxGateSteps = 1000;
inline constexpr std::size_t gateSteps = 5;

inline constexpr std::string_view visual = "bar";
inline constexpr bool             quadratic = false;

} // namespace defaults
