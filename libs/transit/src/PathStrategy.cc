#include "PathStrategy.h"

/**
 * @brief Constructs a PathStrategy object with a given path.
 *
 * This constructor initializes a PathStrategy object with a specified path. The
 * path is a series of coordinates (vectors) that the entity will follow.
 *
 * @param p A vector of vector of floats representing the path coordinates.
 */
PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
    : path(p), index(0) {}

/**
 * @brief Moves an entity along the defined path.
 *
 * This method updates the position and direction of the entity based on the
 * path defined for this strategy. It calculates the next position based on the
 * entity's current position, speed, and the time delta.
 *
 * @param entity Pointer to the IEntity object which is being moved.
 * @param dt The time delta in seconds.
 */
void PathStrategy::move(IEntity* entity, double dt) {
  if (isCompleted()) return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() + dir * entity->getSpeed() * dt);
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4) index++;
}

/**
 * @brief Checks if the path traversal is completed.
 *
 * @return True if the path is completed, otherwise false.
 */
bool PathStrategy::isCompleted() { return index >= path.size(); }

/**
 * @brief Retrieves the path associated with this strategy.
 *
 * @return A vector of vector of floats representing the path coordinates.
 */
std::vector<std::vector<float>> PathStrategy::getPath() { return path; }
