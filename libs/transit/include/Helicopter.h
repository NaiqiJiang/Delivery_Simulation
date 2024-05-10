#ifndef Helicopter_H_
#define Helicopter_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief A class representing a Helicopter entity in the simulation.
 *
 * The Helicopter class extends IEntity and is designed for aerial movement
 * within the simulation environment. It includes functionalities to update
 * its state and handle its specific movement strategies.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the drone's information
   */
  Helicopter(JsonObject& obj);

  /**
   * @brief Destroy the Helicopter object.
   *
   * Responsible for cleaning up resources allocated by the Helicopter, ensuring
   * proper memory management.
   */
  ~Helicopter();

  /**
   * @brief Update the state of the Helicopter.
   *
   * This method updates the Helicopter's state based on the time delta. It
   * includes managing its movement and any other behaviors specific to the
   * Helicopter.
   *
   * @param dt Time delta for updating the state.
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif
