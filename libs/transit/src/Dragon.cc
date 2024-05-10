#define _USE_MATH_DEFINES
#include "Dragon.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

/**
 * @brief Construct a new Dragon object.
 *
 * Initializes a Dragon entity with properties specified in the given JSON
 * object. Sets the Dragon as initially available for package deliveries.
 *
 * @param obj JSON object containing the configuration for the Dragon.
 */
Dragon::Dragon(JsonObject& obj) : IEntity(obj) { available = true; }

/**
 * @brief Destroy the Dragon object.
 *
 * Cleans up allocated memory for the strategies associated with packages and
 * final destinations.
 */
Dragon::~Dragon() {
  for (size_t i = 0; i < toPackage.size(); i++) {
    delete toPackage.at(i);
    delete toFinalDestination.at(i);
  }
}

/**
 * @brief Retrieves and sets up the next delivery tasks for the Dragon.
 *
 * This method determines and prepares the next set of delivery tasks based on
 * the Dragon's capacity and the available deliveries in the simulation model.
 */
void Dragon::getNextDelivery() {
  std::vector<Vector3> packagePosition;
  std::vector<Vector3> finalDestination;

  int numDeliveries =
      std::min(static_cast<int>(model->scheduledDeliveriesOver50.size()),
               this->maxCapacity);
  this->currentLoad = numDeliveries;

  packages.resize(numDeliveries, nullptr);
  toPackage.resize(numDeliveries, nullptr);
  toFinalDestination.resize(numDeliveries, nullptr);
  pickedUp.resize(numDeliveries, false);
  packagePosition.resize(numDeliveries);
  finalDestination.resize(numDeliveries);

  if (this->currentLoad == this->maxCapacity) {
    fullLoaded = true;
  } else {
    fullLoaded = false;
  }

  for (int i = 0; i < currentLoad; i++) {
    if (model && !model->scheduledDeliveriesOver50.empty()) {
      packages.at(i) = model->scheduledDeliveriesOver50.front();
      model->scheduledDeliveriesOver50.erase(
          model->scheduledDeliveriesOver50.begin());
    }
  }

  for (int i = 0; i < this->currentLoad; i++) {
    if (packages.at(i)) {
      available = false;
      pickedUp.at(i) = false;

      packagePosition.at(i) = packages.at(i)->getPosition();
      finalDestination.at(i) = packages.at(i)->getDestination();

      toPackage.at(i) = new BeelineStrategy(position, packagePosition.at(i));

      std::string strat = packages.at(i)->getStrategyName();
      if (strat == "astar") {
        toFinalDestination.at(i) = new JumpDecorator(new AstarStrategy(
            packagePosition.at(i), finalDestination.at(i), model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination.at(i) = new SpinDecorator(new JumpDecorator(
            new DfsStrategy(packagePosition.at(i), finalDestination.at(i),
                            model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination.at(i) = new SpinDecorator(new SpinDecorator(
            new BfsStrategy(packagePosition.at(i), finalDestination.at(i),
                            model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination.at(i) = new JumpDecorator(new SpinDecorator(
            new DijkstraStrategy(packagePosition.at(i), finalDestination.at(i),
                                 model->getGraph())));
      } else {
        toFinalDestination.at(i) =
            new BeelineStrategy(packagePosition.at(i), finalDestination.at(i));
      }
    }
  }
}

// void Dragon::update(double dt) {
//     if (available)
//         getNextDelivery();

//     if (this->currentLoad > 0) {
//         if (toPackage.at(packageIndex)) {
//             toPackage.at(packageIndex)->move(this, dt);

//             if (toPackage.at(packageIndex)->isCompleted()) {
//                 delete toPackage.at(packageIndex);
//                 toPackage.at(packageIndex) = nullptr;
//                 pickedUp.at(packageIndex) = true;
//             }
//         } else if (toFinalDestination.at(packageIndex)) {
//             toFinalDestination.at(packageIndex)->move(this, dt);

//             if (packages.at(packageIndex) && pickedUp.at(packageIndex)) {
//                 packages.at(packageIndex)->setPosition(position);
//                 packages.at(packageIndex)->setDirection(direction);
//             }

//             if (toFinalDestination.at(packageIndex)->isCompleted()) {
//                 delete toFinalDestination.at(packageIndex);
//                 toFinalDestination.at(packageIndex) = nullptr;
//                 packages.at(packageIndex)->handOff();
//                 packages.at(packageIndex) = nullptr;
//                 pickedUp.at(packageIndex) = false;
//                 this->currentLoad--;
//                 packageIndex++;
//             }

//             if (this->currentLoad == 0) {
//                 available = true;
//                 packageIndex = 0;
//             }
//         }
//     }
// }

/**
 * @brief Update the state of the Dragon.
 *
 * This method updates the Dragon's state based on the time delta. It handles
 * the delivery process, including moving towards packages and final
 * destinations, and updating package positions.
 *
 * @param dt Time delta for updating the state.
 */
void Dragon::update(double dt) {
  if (available) getNextDelivery();

  if (this->currentLoad > 0) {
    if (numPicked != this->currentLoad && toPackage.at(packageIndex)) {
      if (numPicked > 0) {
        packages.at(tempPickedIndex)->setPosition(position);
        packages.at(tempPickedIndex)->setDirection(direction);
      }
      toPackage.at(packageIndex)->move(this, dt);
      if (toPackage.at(packageIndex)->isCompleted()) {
        delete toPackage.at(packageIndex);
        toPackage.at(packageIndex) = nullptr;
        pickedUp.at(packageIndex) = true;
        if (packages.at(packageIndex) && pickedUp.at(packageIndex)) {
          packages.at(packageIndex)->setPosition(position);
          packages.at(packageIndex)->setDirection(direction);
        }
        packageIndex++;
        numPicked++;
      }
    } else if (numPicked == this->currentLoad &&
             toFinalDestination.at(packageIndex2)) {
      toFinalDestination.at(packageIndex2)->move(this, dt);
      if (this->currentLoad == 2) {
        packages.at(tempPickedIndex)->setPosition(position);
        packages.at(tempPickedIndex)->setDirection(direction);
      }
      if (this->currentLoad != 1) {
        packages.at(1)->setPosition(position);
        packages.at(1)->setDirection(direction);
      }
      if (this->currentLoad == 1 && !fullLoaded) {
        packages.at(tempPickedIndex)->setPosition(position);
        packages.at(tempPickedIndex)->setDirection(direction);
      } else if (this->currentLoad == 1) {
        packages.at(1)->setPosition(position);
        packages.at(1)->setDirection(direction);
      }

      if (toFinalDestination.at(packageIndex2)->isCompleted()) {
        delete toFinalDestination.at(packageIndex2);
        toFinalDestination.at(packageIndex2) = nullptr;
        packages.at(packageIndex2)->handOff();
        packages.at(packageIndex2) = nullptr;
        pickedUp.at(packageIndex2) = false;
        this->currentLoad--;
        numPicked--;
        packageIndex2++;
      }
      if (this->currentLoad == 0) {
        available = true;
        packageIndex = 0;
        packageIndex2 = 0;
      }
    }
  }
}
