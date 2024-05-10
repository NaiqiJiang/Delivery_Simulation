#ifndef CHARGER_H
#define CHARGER_H

#include <cstdlib>
#include <ctime>
#include <vector>

#include "AstarStrategy.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "SimulationModel.h"
#include "math/vector3.h"

/**
 * @class Charger
 * @brief Represents a Charger in a simulation environment.
 *
 * The Charger class, extending IEntity, is designed to simulate a charging
 * station within the simulation. Chargers may be used to recharge other
 * entities like drones or robots within the system. This class may include
 * functionalities specific to handling charging mechanisms and interactions
 * with other entities.
 */
class Charger : public IEntity {
 public:
  /**
   * @brief Construct a new Charger object.
   *
   * Initializes a Charger entity with properties specified in the given JSON
   * object. This typically includes setting up its initial state and any
   * specific attributes related to the charger's functionality in the
   * simulation.
   *
   * @param obj JSON object containing the Charger's configuration.
   */
  Charger(JsonObject& obj);

  /**
   * @brief Update the state of the Charger.
   *
   * This method updates the Charger's state based on the time delta. It might
   * include managing charging processes or interactions with other entities in
   * the simulation.
   *
   * @param dt Time delta for updating the state.
   */
  void update(double dt);
};

#endif
