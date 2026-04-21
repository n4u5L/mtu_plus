#pragma once

#include <cstdint>

namespace core {

typedef int32_t Fixed;

struct FixedPoint {
  Fixed x, y;
};

} // namespace core