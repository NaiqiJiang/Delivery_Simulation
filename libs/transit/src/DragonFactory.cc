#include "DragonFactory.h"

#include "Dragon.h"

/**
 * @brief Creates a Dragon entity based on the provided JSON object.
 *
 * This method is responsible for interpreting the JSON object and creating a
 * new Dragon entity if the type matches 'dragon'. It outputs a message upon
 * successful creation of a Dragon entity.
 *
 * @param entity JSON object containing the configuration data for the entity.
 * @return IEntity* Pointer to the newly created Dragon entity, or nullptr if
 * the type does not match 'dragon'.
 */
IEntity* DragonFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("dragon") == 0) {
    std::cout << "Dragon Created" << std::endl;
    return new Dragon(entity);
  }
  return nullptr;
}
