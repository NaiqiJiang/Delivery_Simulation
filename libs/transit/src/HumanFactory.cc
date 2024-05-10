#include "HumanFactory.h"

/**
 * @brief Creates a Human entity based on the provided JSON object.
 *
 * This method is responsible for interpreting the JSON object and creating a
 * new Human entity if the type matches 'human'. It outputs a message upon
 * successful creation of a Human entity.
 *
 * @param entity JSON object containing the configuration data for the entity.
 * @return IEntity* Pointer to the newly created Human entity, or nullptr if the
 * type does not match 'human'.
 */
IEntity* HumanFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("human") == 0) {
    std::cout << "Human Created" << std::endl;
    return new Human(entity);
  }
  return nullptr;
}
