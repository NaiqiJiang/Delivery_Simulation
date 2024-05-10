#include "Robot.h"

/**
 * @brief Constructs a Robot object from a JsonObject.
 *
 * This constructor initializes a Robot object using the details provided in a
 * JsonObject.
 *
 * @param obj Reference to a JsonObject containing robot details.
 */
Robot::Robot(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Updates the robot's state. This method is currently a placeholder and
 * does not perform any operation.
 *
 * @param dt The delta time in seconds.
 */
void Robot::update(double dt) {}

/**
 * @brief Receives a package and stores it.
 *
 * This method assigns a WeightDecorator-wrapped package to the robot.
 *
 * @param p Pointer to the WeightDecorator object wrapping the package.
 */
void Robot::receive(WeightDecorator* p) { package = p; }
