#include "ICelebrationDecorator.h"

/**
 * @brief Construct a new ICelebrationDecorator object.
 *
 * Initializes a ICelebrationDecorator with an underlying strategy and a
 * specified time duration for the celebration. The decorator enhances the
 * original strategy with an additional celebration action.
 *
 * @param strategy Pointer to the IStrategy object to be decorated.
 * @param time Duration in seconds for the celebration behavior.
 */
ICelebrationDecorator::ICelebrationDecorator(IStrategy* strategy, double time) {
  this->strategy = strategy;
  this->time = time;
}

/**
 * @brief Destroy the ICelebrationDecorator object.
 *
 * Cleans up resources, specifically the decorated strategy object.
 */
ICelebrationDecorator::~ICelebrationDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

/**
 * @brief Moves the entity according to the decorated strategy and celebration
 * behavior.
 *
 * First, the method applies the underlying strategy. Once the strategy is
 * completed, it starts the celebration behavior for the specified duration.
 *
 * @param entity Entity to move.
 * @param dt Delta time for the movement and celebration updates.
 */
void ICelebrationDecorator::move(IEntity* entity, double dt) {
  if (!strategy->isCompleted()) {
    strategy->move(entity, dt);
  } else if (!isCompleted()) {
    celebrate(entity, dt);
    time -= dt;
  }
}

/**
 * @brief Checks if the celebration behavior is completed.
 *
 * @return True if the celebration is complete, false otherwise.
 */
bool ICelebrationDecorator::isCompleted() { return time <= 0; }
