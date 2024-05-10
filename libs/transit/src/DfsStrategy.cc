#include "DfsStrategy.h"

#include "routing/depth_first_search.h"

/**
 * @brief Constructs a DfsStrategy object.
 *
 * Initializes the DfsStrategy by converting the starting and ending positions
 * from Vector3 to std::vector<float> and then computing the path using the
 * Depth-First Search algorithm. This strategy is designed to find a path from a
 * starting position to a destination in a graph-based environment using DFS,
 * which explores as far as possible along each branch before backtracking.
 *
 * @param pos Starting position of the entity in Vector3 format.
 * @param des Destination position of the entity in Vector3 format.
 * @param g Pointer to the graph interface used for pathfinding.
 */
DfsStrategy::DfsStrategy(Vector3 pos, Vector3 des, const routing::IGraph* g) {
  std::vector<float> start = {static_cast<float>(pos[0]),
                              static_cast<float>(pos[1]),
                              static_cast<float>(pos[2])};
  std::vector<float> end = {static_cast<float>(des[0]),
                            static_cast<float>(des[1]),
                            static_cast<float>(des[2])};
  path = g->GetPath(start, end, routing::DepthFirstSearch::Default());
}
