#include "ChargerFactory.h"

/**
 * @brief Creates a Charger entity based on the provided JSON object.
 *
 * This method is responsible for interpreting the JSON object and creating a
 * new Charger entity if the type matches 'charger'. It outputs a message upon
 * successful creation of a Charger entity.
 *
 * @param entity JSON object containing the configuration data for the entity.
 * @return IEntity* Pointer to the newly created Charger entity, or nullptr if
 * the type does not match 'charger'.
 */
IEntity* ChargerFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("charger") == 0) {
    std::cout << "Charger Created" << std::endl;
    return new Charger(entity);
  }
  return nullptr;
}
