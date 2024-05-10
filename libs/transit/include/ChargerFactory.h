#ifndef CHARGER_FACTORY_H_
#define CHARGER_FACTORY_H_

#include "Charger.h"
#include "IEntityFactory.h"

/**
 * @brief Factory class for creating Charger entities.
 *
 * ChargerFactory is a concrete implementation of the IEntityFactory interface.
 * It specializes in creating Charger objects, which are entities in the
 * simulation. This factory takes a JSON object as input and constructs a
 * Charger entity based on the provided specifications.
 */
class ChargerFactory : public IEntityFactory {
 public:
  /**
   * @brief Destroy the ChargerFactory object.
   *
   * Virtual destructor ensures proper cleanup of resources that might be
   * acquired by the ChargerFactory instance.
   */
  virtual ~ChargerFactory() {}
  /**
   * @brief Create a Charger entity.
   *
   * This method takes a JSON object representing the specifications of the
   * charger and uses it to create a new Charger entity. The method adheres to
   * the interface contract of IEntityFactory for creating entities.
   *
   * @param entity JSON object containing the specifications for the charger.
   * @return IEntity* Pointer to the newly created Charger entity.
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
