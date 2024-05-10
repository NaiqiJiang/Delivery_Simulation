#include "DuckFactory.h"

/**
 * @brief Creates an entity based on the specified type in the JSON object.
 *
 * This function is responsible for creating entities based on the type
 * specified in the provided JSON object. It currently supports the creation of
 * 'Duck' entities. If the type matches 'duck', a new Duck object is
 * instantiated and returned. If the type does not match any known entity types,
 * the function returns nullptr.
 *
 * @param entity A JsonObject containing the data necessary for entity creation,
 * including the type of entity.
 * @return A pointer to the newly created IEntity, or nullptr if the type is not
 * supported.
 */
IEntity* DuckFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("duck") == 0) {
    std::cout << "Duck Created" << std::endl;
    return new Duck(entity);
  }
  return nullptr;
}
