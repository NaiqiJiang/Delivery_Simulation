#include "CompositeFactory.h"

/**
 * @brief Creates an entity based on the provided JSON object using a composite
 * of factories.
 *
 * This method iterates through all component factories and attempts to create
 * an entity. It returns the entity created by the first factory that
 * successfully creates a non-null entity. If no factory can create the entity,
 * it outputs an error message.
 *
 * @param entity JSON object containing the configuration data for the entity.
 * @return IEntity* Pointer to the newly created entity, or nullptr if no
 * factory could create the entity.
 */
IEntity* CompositeFactory::CreateEntity(JsonObject& entity) {
  for (int i = 0; i < componentFactories.size(); i++) {
    IEntity* createdEntity = componentFactories.at(i)->CreateEntity(entity);
    if (createdEntity != nullptr) {
      return createdEntity;
    }
  }
  std::cout << "[!] Error: Type mismatched..." << std::endl;
  return nullptr;
}

/**
 * @brief Adds a new factory to the composite factory.
 *
 * This method allows for the addition of new component factories to the
 * composite, expanding its ability to create different types of entities.
 *
 * @param factoryEntity Pointer to the factory to be added.
 */
void CompositeFactory::AddFactory(IEntityFactory* factoryEntity) {
  componentFactories.push_back(factoryEntity);
}

/**
 * @brief Destructor for CompositeFactory.
 *
 * Cleans up resources by deleting all component factories that were added to
 * the composite.
 */
CompositeFactory::~CompositeFactory() {
  for (int i = 0; i < componentFactories.size(); i++) {
    delete componentFactories[i];
  }
}
