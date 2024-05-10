#include "AstarStrategy.h"

#include "routing/astar.h"

/**
 * @brief Constructs an AstarStrategy object.
 *
 * Initializes the AstarStrategy by converting the starting and ending positions
 * from Vector3 to std::vector<float> and then computing the path using the A*
 * algorithm. This strategy is designed to find an efficient path from a
 * starting position to a destination in a graph-based environment.
 *
 * @param pos Starting position of the entity in Vector3 format.
 * @param des Destination position of the entity in Vector3 format.
 * @param g Pointer to the graph interface used for pathfinding.
 */
AstarStrategy::AstarStrategy(Vector3 pos, Vector3 des,
                             const routing::IGraph* g) {
  std::vector<float> start = {static_cast<float>(pos[0]),
                              static_cast<float>(pos[1]),
                              static_cast<float>(pos[2])};
  std::vector<float> end = {static_cast<float>(des[0]),
                            static_cast<float>(des[1]),
                            static_cast<float>(des[2])};
  path = g->GetPath(start, end, routing::AStar::Default());
}
