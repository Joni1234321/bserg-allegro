#pragma once
#include "math/mathb-types.h"

#define UNITS_PER_TILE 64
#define LOG_UNITS_PER_TILE 6

// Ignore the first 6 bits, since 2^6 = 64
#define UNITS_PER_TILE_MASK 0xFFC0

mathb::types::int2 TILE_TO_UNIT(const mathb::types::int2 tile);
mathb::types::int2 UNIT_TO_TILE(const mathb::types::int2 unit);
