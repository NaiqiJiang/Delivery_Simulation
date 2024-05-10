#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief A class representing a Human entity in the simulation.
 *
 * The Human class extends IEntity and is designed to simulate human behavior
 * within the simulation environment. It includes functionality to update its
 * state and handle its specific movement and actions.
 */
class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Destroy the Human object.
   *
   * Responsible for cleaning up resources allocated by the Human, ensuring
   * proper memory management.
   */
  ~Human();

  /**
   * @brief Update the state of the Human.
   *
   * This method updates the Human's state based on the time delta. It includes
   * managing its movement and any other behaviors specific to the Human.
   *
   * @param dt Time delta for updating the state.
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif
