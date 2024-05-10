#ifndef DRAGON_H_
#define DRAGON_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "WeightDecorator.h"
#include "math/vector3.h"

class Package;

/**
 * @brief A class representing a Dragon entity in the simulation.
 *
 * The Dragon class extends IEntity and is responsible for handling the
 * logistics of package delivery. It manages package pickups, transportation,
 * and delivery using various strategies. The class also handles constraints
 * like capacity and package handling.
 */
class Dragon : public IEntity {
 public:
  /**
   * @brief Construct a new Dragon object.
   *
   * Initializes a Dragon entity with properties specified in the given JSON
   * object. This includes setting up strategies, capacity, and other relevant
   * attributes.
   *
   * @param obj JSON object containing the configuration for the Dragon.
   */
  Dragon(JsonObject& obj);

  /**
   * @brief Destroy the Dragon object.
   *
   * Responsible for cleaning up resources allocated by the Dragon, ensuring
   * proper memory management.
   */
  ~Dragon();

  /**
   * @brief Retrieves the next delivery task for the Dragon.
   *
   * This method is responsible for determining the next package to be delivered
   * and preparing the Dragon for that task.
   */
  void getNextDelivery();

  /**
   * @brief Update the state of the Dragon.
   *
   * This method updates the Dragon's state based on the time delta, managing
   * its movement, package handling, and other behaviors.
   *
   * @param dt Time delta for updating the state.
   */
  void update(double dt);
  Dragon(const Dragon& Dragon) = delete;
  Dragon& operator=(const Dragon& Dragon) = delete;

 private:
  bool available = false;
  std::vector<bool> pickedUp;  // = std::vector<bool>(12, false);
  std::vector<WeightDecorator*>
      packages;  // = std::vector<WeightDecorator*>(12, nullptr);
  std::vector<IStrategy*> toPackage;  // = std::vector<IStrategy*>(12, nullptr);
  std::vector<IStrategy*>
      toFinalDestination;  //  = std::vector<IStrategy*>(12, nullptr);
  const int maxCapacity = 2;
  int currentLoad = 0;
  int packageIndex = 0;
  int packageIndex2 = 0;
  int tempPickedIndex = 0;
  int numPicked = 0;
  bool fullLoaded;
};

#endif
