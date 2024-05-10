#include "BeelineStrategy.h"

/**
 * @brief Construct a new BeelineStrategy object.
 *
 * Initializes a BeelineStrategy with starting and ending positions. This
 * strategy creates a direct, straight-line path between the specified starting
 * position (pos) and destination (des). The path consists of only these two
 * points, representing the most direct route.
 *
 * @param pos Starting position of the entity in Vector3 format.
 * @param des Destination position of the entity in Vector3 format.
 */
BeelineStrategy::BeelineStrategy(Vector3 pos, Vector3 des)
    : PathStrategy({{static_cast<float>(pos[0]), static_cast<float>(pos[1]),
                     static_cast<float>(pos[2])},
                    {static_cast<float>(des[0]), static_cast<float>(des[1]),
                     static_cast<float>(des[2])}}) {}
