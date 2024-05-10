#define _USE_MATH_DEFINES
#include "Helicopter.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"

/**
 * @brief Construct a new Helicopter object.
 *
 * Initializes a Helicopter entity with properties specified in the given JSON
 * object. Inherits initialization behavior from the IEntity class.
 *
 * @param obj JSON object containing the configuration for the Helicopter.
 */
Helicopter::Helicopter(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Destroy the Helicopter object.
 *
 * Cleans up allocated memory for the movement strategy if it exists.
 */
Helicopter::~Helicopter() {
  if (movement) delete movement;
}

/**
 * @brief Update the state and movement of the Helicopter.
 *
 * This method updates the Helicopter's movement based on the time delta. If the
 * current movement strategy is completed, it generates a new random destination
 * and sets up a BeelineStrategy towards it.
 *
 * @param dt Time delta for updating the state and movement.
 */
void Helicopter::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    movement = new BeelineStrategy(position, dest);
  }
}
