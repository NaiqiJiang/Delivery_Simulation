#include "PackageFactory.h"

/**
 * @brief Creates an entity based on the specified type in the JsonObject.
 *
 * This method is part of the PackageFactory class. It checks the type of entity
 * requested and creates the corresponding entity object. If the type is
 * "package", it creates a new Package object, decorates it with
 * WeightDecorator, and returns it. If the type does not match any known
 * entities, it returns nullptr.
 *
 * @param entity Reference to a JsonObject containing details about the entity
 * to be created.
 * @return Pointer to the created IEntity object if the type matches "package",
 * otherwise nullptr.
 */
IEntity* PackageFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("package") == 0) {
    std::cout << "Package Created" << std::endl;
    return new WeightDecorator(new Package(entity));
  }
  return nullptr;
}
