#include "DroneFactory.h"

#include "BatteryDecorator.h"

/**
 * @brief Creates a Drone entity wrapped in a BatteryDecorator based on the
 * provided JSON object.
 *
 * This method is responsible for interpreting the JSON object and creating a
 * new Drone entity if the type matches 'drone'. It then wraps the created Drone
 * in a BatteryDecorator, which adds battery management functionality to the
 * Drone. A message is output upon successful creation of a Drone entity.
 *
 * @param entity JSON object containing the configuration data for the entity.
 * @return IEntity* Pointer to the newly created BatteryDecorator wrapping a
 * Drone entity, or nullptr if the type does not match 'drone'.
 */
IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    // return new Drone(entity);
    Drone* myDrone = new Drone(entity);
    return new BatteryDecorator(myDrone, entity);
  }
  return nullptr;
}
