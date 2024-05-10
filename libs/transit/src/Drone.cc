#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

/**
 * @brief Construct a new Drone object.
 *
 * Initializes a Drone entity with properties specified in the given JSON
 * object. Sets the Drone as initially available for package deliveries.
 *
 * @param obj JSON object containing the configuration for the Drone.
 */
Drone::Drone(JsonObject& obj) : IEntity(obj) { available = true; }

/**
 * @brief Destroy the Drone object.
 *
 * Cleans up allocated memory for the strategies associated with package
 * delivery and final destination.
 */
Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

/**
 * @brief Retrieves and sets up the next delivery task for the Drone.
 *
 * This method determines and prepares the next delivery task based on the
 * available deliveries in the simulation model. It sets the appropriate
 * pathfinding strategies for reaching the package and its final destination.
 */
void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0 &&
      model->scheduledDeliveries.front()->getWeight() <= 50) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

/**
 * @brief Update the state of the Drone.
 *
 * This method updates the Drone's state based on the time delta. It handles the
 * delivery process, including moving towards the package and final destination,
 * and updating package positions.
 *
 * @param dt Time delta for updating the state.
 */
void Drone::update(double dt) {
  if (available) getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);
    if (moving == false) {
      moving = true;
    }

    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      moving = false;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    if (moving == false) {
      moving = true;
    }
    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      moving = false;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

/**
 * @brief Checks if the Drone is currently moving.
 *
 * @return True if the Drone is moving, false otherwise.
 */
bool Drone::isMoving() { return moving; }
