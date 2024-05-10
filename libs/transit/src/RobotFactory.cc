#include "RobotFactory.h"

/**
 * @brief Creates an entity based on the specified type in the JsonObject.
 *
 * This method is a part of the RobotFactory class. It checks the type of entity
 * requested and creates the corresponding entity object. If the type is
 * "robot", it creates a new Robot object and returns it. If the type does not
 * match any known entities, it returns nullptr.
 *
 * @param entity Reference to a JsonObject containing details about the entity
 * to be created.
 * @return Pointer to the created IEntity object if the type matches "robot",
 * otherwise nullptr.
 */
IEntity* RobotFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    std::cout << "Robot Created" << std::endl;
    return new Robot(entity);
  }
  return nullptr;
}
