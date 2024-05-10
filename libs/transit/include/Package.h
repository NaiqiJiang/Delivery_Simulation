#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class Robot;

/**
 * @brief A class representing a Package entity in the simulation.
 *
 * The Package class extends IEntity and is responsible for handling the
 * logistics of package information, including its destination, associated
 * strategy, and owner. It also manages the package's position and delivery
 * status.
 */
class Package : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the package's information
   */
  Package(JsonObject& obj);

  /**
   * @brief Gets the Package's destination
   * @return The Package's destination
   */
  Vector3 getDestination() const;

  /**
   * @brief Returns the name of the strategy for this package
   *
   * @returns String name of strategy
   */
  std::string getStrategyName() const;

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  void setStrategyName(std::string strategyName_);

  /**
   * @brief Updates the Package
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

  /**
   * @brief Sets the attributes for delivery
   *
   * @param owner Robot for the package to be delivered to
   */
  void initDelivery(Robot* owner);

  /**
   * @brief Get the owner of the package.
   *
   * @return Robot* pointing to the Robot responsible for delivering the
   * package.
   */
  Robot* getOwner();

  bool requiresDelivery = true;

  /**
   * @brief Get the name of the package.
   *
   * @return String representing the name of the package.
   */
  std::string getName();

  /**
   * @brief Get the current position of the package.
   *
   * @return Vector3 representing the current position of the package.
   */
  Vector3 getPosition() const;

  /**
   * @brief Set the position of the package.
   *
   * @param pos_ Vector3 representing the new position of the package.
   */
  void setPosition(Vector3 pos_);

 private:
  Vector3 destination;
  std::string strategyName;
  Robot* owner = nullptr;
  std::string name;
  Vector3 position;
};

#endif  // PACKAGE_H
