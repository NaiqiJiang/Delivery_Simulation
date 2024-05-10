#include "SpinDecorator.h"

/**
 * @brief Constructs a SpinDecorator object.
 *
 * This constructor initializes a SpinDecorator object with a given strategy,
 * time for the decoration, and a spin speed. The SpinDecorator is used to add
 * spinning behavior to an entity's celebration routine.
 *
 * @param strategy Pointer to an IStrategy object that the decorator will
 * augment.
 * @param time The duration for which the decoration is active.
 * @param spinSpeed The speed at which the entity will spin.
 */
SpinDecorator::SpinDecorator(IStrategy* strategy, double time, double spinSpeed)
    : ICelebrationDecorator(strategy, time), spinSpeed(spinSpeed) {}

/**
 * @brief Executes the spin celebration behavior on an entity.
 *
 * This method makes the entity rotate at a rate determined by its speed and the
 * specified spin speed.
 *
 * @param entity Pointer to the IEntity object that will perform the
 * celebration.
 * @param dt The delta time in seconds.
 */
void SpinDecorator::celebrate(IEntity* entity, double dt) {
  entity->rotate(dt * entity->getSpeed() * spinSpeed);
}
