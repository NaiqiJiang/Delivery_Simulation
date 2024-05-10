#include "HelicopterFactory.h"

/**
 * @brief Creates a Helicopter entity based on the provided JSON object.
 *
 * This method is responsible for interpreting the JSON object and creating a
 * new Helicopter entity if the type matches 'helicopter'. It outputs a message
 * upon successful creation of a Helicopter entity.
 *
 * @param entity JSON object containing the configuration data for the entity.
 * @return IEntity* Pointer to the newly created Helicopter entity, or nullptr
 * if the type does not match 'helicopter'.
 */
IEntity* HelicopterFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("helicopter") == 0) {
    std::cout << "Helicopter Created" << std::endl;
    return new Helicopter(entity);
  }
  return nullptr;
}
