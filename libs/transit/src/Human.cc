#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

/**
 * @brief Construct a new Human object.
 *
 * Initializes a Human entity with properties specified in the given JSON
 * object. Inherits initialization behavior from the IEntity class.
 *
 * @param obj JSON object containing the configuration for the Human.
 */
Human::Human(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Destroy the Human object.
 *
 * Cleans up allocated memory for the movement strategy if it exists.
 */
Human::~Human() {
  if (movement) delete movement;
}

/**
 * @brief Update the state and movement of the Human.
 *
 * This method updates the Human's movement based on the time delta. If the
 * current movement strategy is completed, it generates a new random destination
 * and sets up an AstarStrategy towards it, if a model is available.
 *
 * @param dt Time delta for updating the state and movement.
 */
void Human::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }
}
