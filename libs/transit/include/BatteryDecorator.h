#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H

#include <cmath>
#include <stdexcept>
#include <vector>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Drone.h"
#include "IEntity.h"
#include "PathStrategy.h"

/**
 * @brief A decorator class for Drone that manages its battery usage.
 *
 * BatteryDecorator is a class that extends IEntity and provides additional
 * functionalities to a Drone object, mainly focusing on battery management.
 * It includes methods for updating battery status, calculating distances for
 * battery consumption, and managing charging.
 */
class BatteryDecorator : public IEntity {
 public:
  /**
   * @brief A decorator class for Drone that manages its battery usage.
   *
   * BatteryDecorator is a class that extends IEntity and provides additional
   * functionalities to a Drone object, mainly focusing on battery management.
   * It includes methods for updating battery status, calculating distances for
   * battery consumption, and managing charging.
   */
  BatteryDecorator(Drone* drone, JsonObject& obj);

  /**
   * @brief Destroy the BatteryDecorator object.
   */
  ~BatteryDecorator();

  /**
   * @brief Update the battery status based on the time delta.
   *
   * @param dt Time delta for updating the battery status.
   */
  void update(double dt);

  /**
   * @brief Calculate the total distance of a given path strategy.
   *
   * @param strategy The path strategy for which the total distance is
   * calculated.
   * @return The total distance of the path.
   */
  float calculateTotalDistance(PathStrategy* strategy);

  /**
   * @brief Calculate the distance between two points.
   *
   * @param p1 The first point.
   * @param p2 The second point.
   * @return The distance between p1 and p2.
   */
  float calculate2PointsDistance(Vector3 p1, Vector3 p2);

  /**
   * @brief Check if the battery is sufficient for the next task.
   *
   * @param dt Time delta to estimate battery consumption.
   * @return True if battery is sufficient, False otherwise.
   */
  bool isBatterySufficientForNextTask(double dt);

  /**
   * @brief Charge the battery based on the time delta.
   *
   * @param dt Time delta for charging the battery.
   */
  void chargeBattery(double dt);

  /**
   * @brief Manage the battery during the drone's operation.
   *
   * @param dt Time delta for battery management.
   */
  void manageBattery(double dt);

  /**
   * @brief Consume the battery based on rate and time.
   *
   * @param rate The rate of battery consumption.
   * @param time The time duration for consumption.
   */
  void consumeBattery(double rate, double time);

  /**
   * @brief Find the nearest charging station for the drone.
   *
   * @return The position of the nearest charger.
   */
  Vector3 findCharger();

  /**
   * @brief Link the BatteryDecorator with the simulation model.
   *
   * This method is used to connect the BatteryDecorator with the
   * overall simulation model, ensuring that it can interact
   * properly within the simulated environment.
   *
   * @param model The simulation model to be linked.
   */
  virtual void linkModel(SimulationModel* model) {
    this->model = model;
    decoratedDrone->linkModel(model);
  }

  /**
   * @brief Get the ID of the decorated drone.
   *
   * @return The ID of the drone.
   */
  virtual int getId() const { return decoratedDrone->getId(); }

  /**
   * @brief Get the current position of the decorated drone.
   *
   * @return The position of the drone.
   */
  virtual Vector3 getPosition() const { return decoratedDrone->getPosition(); }

  /**
   * @brief Get the current direction of the decorated drone.
   *
   * @return The direction of the drone.
   */
  virtual Vector3 getDirection() const {
    return decoratedDrone->getDirection();
  }

  /**
   * @brief Get the current detail of the decorated drone.
   *
   * @return The detail of the drone.
   */
  virtual const JsonObject& getDetails() const {
    return decoratedDrone->getDetails();
  }

  /**
   * @brief Get the current color of the decorated drone.
   *
   * @return The color of the drone.
   */
  virtual std::string getColor() const { return decoratedDrone->getColor(); }

  /**
   * @brief Get the current name of the decorated drone.
   *
   * @return The name of the drone.
   */
  virtual std::string getName() const { return decoratedDrone->getName(); }

  /**
   * @brief Get the current speed of the decorated drone.
   *
   * @return The speed of the drone.
   */
  virtual double getSpeed() const { return decoratedDrone->getSpeed(); }

  /**
   * @brief Set the position of the decorated drone.
   *
   * @param pos_ The new position for the drone.
   */
  virtual void setPosition(Vector3 pos_) { decoratedDrone->setPosition(pos_); }

  /**
   * @brief Set the direction of the decorated drone.
   *
   * @param pos_ The new direction for the drone.
   */
  virtual void setDirection(Vector3 dir_) {
    decoratedDrone->setDirection(dir_);
  }

  /**
   * @brief Set the color of the decorated drone.
   *
   * @param pos_ The new color for the drone.
   */
  virtual void setColor(std::string col_) { decoratedDrone->setColor(col_); }

  /**
   * @brief Rotate the decorated drone by a specified angle.
   *
   * @param angle The angle in degrees to rotate the drone.
   */
  virtual void rotate(double angle) { decoratedDrone->rotate(angle); }

 private:
  Drone* decoratedDrone;
  double batteryLevel;
  double stationaryConsumptionRate;
  double movingConsumptionRate;
  IStrategy* go = nullptr;
  IStrategy* back = nullptr;
  std::vector<Vector3> listOfCharger = {Vector3(498.292, 270, -228.623),
                                        Vector3(-698.510, 254.664, 13.222),
                                        Vector3(-282.063, 254.664, -95.990),
                                        Vector3(143.436, 254.664, -107.486),
                                        Vector3(-23.485, 254.664, -93.116),
                                        Vector3(-255.850, 254.664, -236.818),
                                        Vector3(-22.485, 254.664, -228.195),
                                        Vector3(264.146, 254.664, -219.573),
                                        Vector3(-309.223, 254.664, 85.073),
                                        Vector3(113.259, 254.664, 217.279),
                                        Vector3(390.891, 254.664, 277.633),
                                        Vector3(-918.805, 254.664, 47.711),
                                        Vector3(-903.716, 254.664, -170.715),
                                        Vector3(-939.929, 254.664, 314.996),
                                        Vector3(-816.202, 254.664, 562.163),
                                        Vector3(-656.262, 254.664, 309.248),
                                        Vector3(-562.712, 254.664, 579.407),
                                        Vector3(-1063.656, 254.664, 562.163),
                                        Vector3(-1244.720, 254.664, 214.405),
                                        Vector3(37.816, 254.664, -472.488),
                                        Vector3(396.926, 254.664, 16.096),
                                        Vector3(635.327, 254.664, -95.990),
                                        Vector3(743.965, 254.664, 162.672),
                                        Vector3(571.955, 254.664, -294.298),
                                        Vector3(170.596, 254.664, -679.419)};
  int toCharge = 0;  // 1 stands for true, which we need to charge
};
#endif  // BATTERY_DECORATOR_H_
