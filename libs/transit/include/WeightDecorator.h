#ifndef WEIGHT_DECORATOR_H_
#define WEIGHT_DECORATOR_H_

#include "Package.h"
#include "math/vector3.h"

/**
 * @class WeightDecorator
 * @brief Decorator class for adding weight attributes to Package entities.
 *
 * This class extends IEntity and acts as a decorator for the Package class,
 * adding weight handling capabilities. It encapsulates a Package and provides
 * additional functionalities related to the weight of the package.
 */
class WeightDecorator : public IEntity {
 public:
  /**
   * @brief Construct a new WeightDecorator object.
   *
   * @param package Pointer to the Package object that is being decorated.
   */
  WeightDecorator(Package* package);

  // Override functions from IEntity
  Vector3 getDestination() const;
  Vector3 getPosition() const;
  std::string getStrategyName() const;
  void setStrategyName(std::string strategyName_);
  void update(double dt);
  void initDelivery(Robot* owner);
  Robot* getOwner() const;
  std::string getName() const override;
  const JsonObject& getDetails() const override;
  void handOff();
  // Specific function for WeightDecorator
  /**
   * @brief Get the weight of the decorated package.
   *
   * @return double representing the weight of the package.
   */
  double getWeight() const;
  bool requiresDelivery = false;

  /**
   * @brief Set the position of the decorated package.
   *
   * @param pos_ Vector3 representing the new position of the package.
   */
  void setPosition(Vector3 pos_);

 private:
  Package* package;  // Pointer to the wrapped Package object
  double weight;     // Additional attribute
  Vector3 position = package->getPosition();
};
#endif
