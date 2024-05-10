#include "JumpDecorator.h"

/**
 * @brief Construct a new JumpDecorator object.
 *
 * Initializes a JumpDecorator with an underlying strategy, a time duration for
 * the jump behavior, and a specified jump height. This decorator enhances the
 * original strategy by adding a jumping action for the entity.
 *
 * @param strategy Pointer to the IStrategy object to be decorated.
 * @param time Duration in seconds for the jump behavior.
 * @param jumpHeight Height of the jump in units.
 */
JumpDecorator::JumpDecorator(IStrategy* strategy, double time,
                             double jumpHeight)
    : ICelebrationDecorator(strategy, time), jumpHeight(jumpHeight) {}

/**
 * @brief Executes the jumping celebration behavior for the entity.
 *
 * This method updates the entity's position to simulate a jumping motion. The
 * entity moves up to the specified jump height and then descends back down.
 *
 * @param entity Entity to apply the jumping behavior to.
 * @param dt Delta time for the update.
 */
void JumpDecorator::celebrate(IEntity* entity, double dt) {
  Vector3 step(0, entity->getSpeed() * dt, 0);
  if (up) {
    h += step.y;
    entity->setPosition(entity->getPosition() + step);
    if (h >= jumpHeight) up = false;
  } else {
    h -= step.y;
    entity->setPosition(entity->getPosition() - step);
    if (h <= 0) up = true;
  }
}
