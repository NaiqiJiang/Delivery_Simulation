#include "Package.h"

#include "Robot.h"

/**
 * @brief Constructs a Package object from a JsonObject.
 *
 * This constructor initializes a Package object using the details provided in a
 * JsonObject. It extracts the name and position of the package from the object.
 *
 * @param obj Reference to a JsonObject containing package details.
 */
Package::Package(JsonObject& obj) : IEntity(obj) {
  std::string n = details["name"];
  name = n;
  JsonArray pos(details["position"]);
  position = {pos[0], pos[1], pos[2]};
}

/**
 * @brief Gets the destination of the package.
 *
 * @return The destination as a Vector3 object.
 */
Vector3 Package::getDestination() const { return destination; }

/**
 * @brief Retrieves the strategy name for the package delivery.
 *
 * @return A string representing the delivery strategy name.
 */
std::string Package::getStrategyName() const { return strategyName; }

/**
 * @brief Sets the strategy name for the package delivery.
 *
 * @param strategyName_ The new strategy name as a string.
 */
void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

/**
 * @brief Gets the name of the package.
 *
 * @return The name of the package as a string.
 */
std::string Package::getName() { return name; }

/**
 * @brief Retrieves the current position of the package.
 *
 * @return The position of the package as a Vector3 object.
 */
Vector3 Package::getPosition() const { return position; }

/**
 * @brief Updates the package's state. This method is currently a placeholder
 * and does not perform any operation.
 *
 * @param dt The delta time in seconds.
 */
void Package::update(double dt) {}

/**
 * @brief Sets the position of the package.
 *
 * @param pos_ The new position of the package as a Vector3 object.
 */
void Package::setPosition(Vector3 pos_) { position = pos_; }

/**
 * @brief Initializes the delivery process of the package.
 *
 * This method assigns a Robot as the owner of the package and sets the
 * destination of the package to the Robot's position.
 *
 * @param owner Pointer to the Robot which will deliver the package.
 */
void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery = false;
  destination = owner->getPosition();
}

/**
 * @brief Gets the Robot that is the owner or the deliverer of the package.
 *
 * @return Pointer to the Robot object.
 */
Robot* Package::getOwner() { return owner; }
