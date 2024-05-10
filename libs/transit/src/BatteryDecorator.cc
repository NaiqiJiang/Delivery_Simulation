#include "BatteryDecorator.h"

#include <vector>

#include "JumpDecorator.h"
#include "SpinDecorator.h"

/**
 * @brief Construct a new BatteryDecorator object.
 *
 * Initializes a BatteryDecorator with a specified drone and JSON configuration
 * object. Sets up initial battery level and consumption rates.
 *
 * @param drone Pointer to the Drone object being decorated.
 * @param obj JSON object containing configuration data.
 */
BatteryDecorator::BatteryDecorator(Drone* drone, JsonObject& obj)
    : IEntity(obj) {
  go = nullptr;
  back = nullptr;
  decoratedDrone = drone;
  batteryLevel = 100.0;           // start with a full battery
  stationaryConsumptionRate = 0.5;
}

/**
 * @brief Destroy the BatteryDecorator object.
 *
 * Cleans up resources, including the decorated drone object.
 */
BatteryDecorator::~BatteryDecorator() { delete decoratedDrone; }

/**
 * @brief Calculate the Euclidean distance between two points in 3D space.
 *
 * @param p1 First point.
 * @param p2 Second point.
 * @return Distance between p1 and p2.
 */
float BatteryDecorator::calculate2PointsDistance(Vector3 p1, Vector3 p2) {
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  double dz = p2.z - p1.z;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

/**
 * @brief Calculate the total distance of a path defined by a PathStrategy.
 *
 * @param strategy PathStrategy object defining the path.
 * @return Total distance of the path.
 */
float BatteryDecorator::calculateTotalDistance(PathStrategy* strategy) {
  std::vector<std::vector<float>> path = strategy->getPath();
  if (path.size() < 2) {
    throw std::invalid_argument("Path must contain at least two points");
  }
  float totalDistance = 0.0f;

  for (size_t i = 1; i < path.size(); ++i) {
    if (path[i].size() != 3 || path[i - 1].size() != 3) {
      throw std::invalid_argument(
          "Each point must have exactly three coordinates (x, y, and z)");
    }

    float dx = path[i][0] - path[i - 1][0];
    float dy = path[i][1] - path[i - 1][1];
    float dz = path[i][2] - path[i - 1][2];
    totalDistance += std::sqrt(dx * dx + dy * dy + dz * dz);
  }
  return totalDistance;
}

/**
 * @brief Check if the battery level is sufficient for the next task.
 *
 * @param dt Time delta for estimating battery consumption.
 * @return True if battery is sufficient, False otherwise.
 */
bool BatteryDecorator::isBatterySufficientForNextTask(double dt) {
  std::cout << "isBatterySufficientForNextTask is called" << std::endl;
  double distance1;
  double distance2;
  if (toCharge == 1) {
    return false;
  }
  if (decoratedDrone->available) {
    decoratedDrone->getNextDelivery();
    if (decoratedDrone->toPackage || decoratedDrone->toFinalDestination) {
      PathStrategy* pathStrategy1 =
          dynamic_cast<PathStrategy*>(decoratedDrone->toPackage);
      PathStrategy* pathStrategy2 =
          dynamic_cast<PathStrategy*>(decoratedDrone->toFinalDestination);
      if (pathStrategy1) {
        // to compute the distance between drone and the package
        distance1 = calculateTotalDistance(pathStrategy1);
      }
      if (pathStrategy2) {
        // to compute the distance between the package and the person
        distance2 = calculateTotalDistance(pathStrategy2);
      }
      double totalDistance = distance1 + distance2;
      double flyableDistance =
          batteryLevel / stationaryConsumptionRate * decoratedDrone->getSpeed();
      if (flyableDistance > totalDistance) {
        return true;
      } else {
        toCharge = 1;
        return false;
      }

    } else {
      return true;
    }
  }
  return true;
}

/**
 * @brief Update the state and battery level of the decorated drone.
 *
 * @param dt Time delta for updating the state.
 */
void BatteryDecorator::update(double dt) {
  manageBattery(dt);
  std::cout << "this is my battery volume right now!" << batteryLevel
            << std::endl;
  if (batteryLevel < 0) {
    std::cout << "this drone out of battery" << std::endl;
  }
}

/**
 * @brief Find the nearest charging station to the drone.
 *
 * @return Position of the nearest charger.
 */
Vector3 BatteryDecorator::findCharger() {
  std::cout << "findCharger is called" << std::endl;
  // Assuming `position` is a member variable of BatteryDecorator class
  // representing its position
  Vector3 nearestCharger;
  if (listOfCharger.empty()) {
    // Handle the case where there are no chargers
    std::cerr << "No chargers available." << std::endl;
    return Vector3();  // Return a default Vector3, maybe representing an error
                       // or invalid state
  }

  double minDistance = std::numeric_limits<double>::max();

  for (const Vector3& charger : listOfCharger) {
    double distance =
        calculate2PointsDistance(decoratedDrone->getPosition(), charger);
    if (distance < minDistance) {
      minDistance = distance;
      nearestCharger = charger;
    }
  }
  return nearestCharger;
}

/**
 * @brief Charge the battery of the drone.
 *
 * Handles the process of moving the drone to the charger, charging, and
 * returning.
 *
 * @param dt Time delta for charging process.
 */
void BatteryDecorator::chargeBattery(double dt) {
  std::cout << "chargeBattery is called" << std::endl;
  // go to the charger then come back! we need to use 2 path strategies
  // first i need to find the station i wanna go!
  if (go == nullptr && back == nullptr) {
    toCharge = 1;
    Vector3 currentPosition = decoratedDrone->getPosition();
    Vector3 charger = findCharger();
    // then make strategy!
    go = new JumpDecorator(
        new SpinDecorator(new BeelineStrategy(currentPosition, charger)));
    back = new BeelineStrategy(charger, currentPosition);
    std::cout << "this is my go path: " << go << std::endl;
    std::cout << "this is my go path: " << back << std::endl;
  }
  if (go) {
    std::cout << "on my way go to the charger" << std::endl;
    go->move(decoratedDrone, dt);
    batteryLevel -= stationaryConsumptionRate * dt;
    if (go->isCompleted()) {
      batteryLevel = 100;
      std::cout << "fully chagred" << std::endl;
      if (back) {
        back->move(decoratedDrone, dt);
        std::cout << "on my way back to the work" << std::endl;
        batteryLevel -= stationaryConsumptionRate * dt;
        if (back->isCompleted()) {
          delete back;
          back = nullptr;
          toCharge = 0;
          delete go;
          go = nullptr;
        }
      }
    }
  }
  // else if (back){
  //     back->move(decoratedDrone,dt);
  //     std:: cout << "on my way back to the work" << std::endl;
  //     batteryLevel -= stationaryConsumptionRate * dt;
  //     if(back->isCompleted()){
  //         delete back;
  //         toCharge = 0;
  //     }
  // }
}

/**
 * @brief Manage the battery during the drone's operation.
 *
 * Decides whether to continue current tasks or to charge the battery based on
 * sufficiency.
 *
 * @param dt Time delta for battery management.
 */
void BatteryDecorator::manageBattery(double dt) {
  std::cout << "manageBattery" << std::endl;
  // no need to call all the time
  if (isBatterySufficientForNextTask(dt)) {
    decoratedDrone->update(dt);
    if (!decoratedDrone->available) {
      batteryLevel -= stationaryConsumptionRate * dt;
    }
    std::cout << "enough battery" << std::endl;
  } else {
    chargeBattery(dt);
  }
}
