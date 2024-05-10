#ifndef BFS_STRATEGY_H_
#define BFS_STRATEGY_H_

#include "PathStrategy.h"
#include "graph.h"

/**
 * @class BfsStrategy
 * @brief Implements a Breadth-First Search (BFS) pathfinding strategy.
 */
class BfsStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new BfsStrategy object.
   *
   * @param position The current starting position.
   * @param destination The end destination for the pathfinding.
   * @param graph The graph representing the nodes and connections in the map.
   */
  BfsStrategy(Vector3 position, Vector3 destination,
              const routing::IGraph* graph);
};
#endif  // BFS_STRATEGY_H_
