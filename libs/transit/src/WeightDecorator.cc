#include "WeightDecorator.h"

#include "Robot.h"

/**
 * @brief Decorates a package with additional weight-related functionality.
 *
 * This decorator adds weight handling to a Package object. It extends the
 * functionality of the package by adding weight-related properties and methods
 * while maintaining the original package behaviors.
 *
 * @param package Pointer to the Package object to be decorated.
 */
WeightDecorator::WeightDecorator(Package* package) : package(package) {
  weight = std::stod(package->getDetails()["weight"]);
  requiresDelivery = true;
  position = package->getPosition();
}

/**
 * @brief Retrieves the destination of the wrapped package.
 *
 * @return The destination as a Vector3 object.
 */
Vector3 WeightDecorator::getDestination() const {
  return package->getDestination();
}

/**
 * @brief Gets the strategy name of the wrapped package.
 *
 * @return A string representing the strategy name.
 */
std::string WeightDecorator::getStrategyName() const {
  return package->getStrategyName();
}

/**
 * @brief Sets the strategy name for the wrapped package.
 *
 * @param strategyName_ The new strategy name as a string.
 */
void WeightDecorator::setStrategyName(std::string strategyName_) {
  package->setStrategyName(strategyName_);
}

/**
 * @brief Updates the state of the wrapped package.
 *
 * @param dt The delta time in seconds.
 */
void WeightDecorator::update(double dt) { package->update(dt); }

/**
 * @brief Initializes the delivery process of the wrapped package.
 *
 * @param owner Pointer to the Robot which will deliver the package.
 */
void WeightDecorator::initDelivery(Robot* owner) {
  package->initDelivery(owner);
}

/**
 * @brief Retrieves the details of the wrapped package as a JsonObject.
 *
 * @return Reference to a JsonObject containing the package details.
 */
const JsonObject& WeightDecorator::getDetails() const {
  return package->getDetails();
}

/**
 * @brief Gets the owner Robot of the wrapped package.
 *
 * @return Pointer to the Robot object.
 */
Robot* WeightDecorator::getOwner() const { return package->getOwner(); }

/**
 * @brief Retrieves the name of the wrapped package.
 *
 * @return The name of the package as a string.
 */
std::string WeightDecorator::getName() const { return package->getName(); }

/**
 * @brief Gets the weight of the package.
 *
 * @return The weight of the package as a double.
 */
double WeightDecorator::getWeight() const { return weight; }

/**
 * @brief Retrieves the current position of the decorated package.
 *
 * @return The position as a Vector3 object.
 */
Vector3 WeightDecorator::getPosition() const { return position; }

/**
 * @brief Hands off the decorated package to its owner.
 *
 * This method is responsible for transferring the responsibility of the package
 * to its owner Robot.
 */
void WeightDecorator::handOff() {
  // Get the owner from the wrapped Package object
  Robot* packageOwner = package->getOwner();

  if (packageOwner) {
    packageOwner->receive(this);
  }
}

/**
 * @brief Sets the position of both the decorator and the wrapped package.
 *
 * @param pos_ The new position as a Vector3 object.
 */
void WeightDecorator::setPosition(Vector3 pos_) {
  position = pos_;
  package->setPosition(pos_);
}
