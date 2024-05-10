#include "Charger.h"

/**
 * @brief Constructor for Charger, initializing with a JSON object.
 *
 * Initializes a Charger entity using a JSON object. Inherits initialization
 * from the IEntity class and sets up initial state for the Charger entity.
 *
 * @param obj JSON object used for initialization.
 */
Charger::Charger(JsonObject& obj) : IEntity(obj) {}

/**
 * @brief Updates the state of the Charger.
 *
 * This method is intended to update the Charger's state based on the time
 * delta. It can include managing charging processes or interactions with other
 * entities in the simulation.
 *
 * @param dt Time delta for updating the state.
 */
void Charger::update(double dt) {}
