#include "SimulationModel.h"

#include "ChargerFactory.h"
#include "DragonFactory.h"
#include "DroneFactory.h"
#include "DuckFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"

/**
 * @brief Constructs a SimulationModel object.
 *
 * This constructor initializes the SimulationModel with various factories to
 * create different types of entities. It adds factories for drones, packages,
 * robots, humans, helicopters, dragons, ducks, and chargers.
 *
 * @param controller Reference to an IController object used to manage the
 * simulation.
 */
SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.AddFactory(new DroneFactory());
  entityFactory.AddFactory(new PackageFactory());  // 也许是这里有问题：3个new。
  entityFactory.AddFactory(new RobotFactory());
  entityFactory.AddFactory(new HumanFactory());
  entityFactory.AddFactory(new HelicopterFactory());
  entityFactory.AddFactory(new DragonFactory());
  entityFactory.AddFactory(new DuckFactory());
  entityFactory.AddFactory(new ChargerFactory());
}

/**
 * @brief Destructor for SimulationModel.
 *
 * Cleans up dynamically allocated memory by deleting all entities and the
 * graph.
 */
SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

/**
 * @brief Creates an entity based on the details provided in a JsonObject.
 *
 * @param entity JsonObject containing the details of the entity to be created.
 * @return Pointer to the newly created IEntity, or nullptr if creation fails.
 */
IEntity* SimulationModel::createEntity(JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.CreateEntity(entity)) {
    // Call AddEntity to add it to the view
    // std::cout << "myNewEntity: " << myNewEntity->getName() << std::endl; //
    // 这里的myNewEntity->getName()打印出来是空的，但是它却可以进入这个if之中，证明myNewEntity不是空指针。不是空指针getName（）却是空的。
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
  }
  return myNewEntity;
}

/**
 * @brief Removes an entity from the simulation by its ID.
 *
 * @param id The ID of the entity to remove.
 */
void SimulationModel::removeEntity(int id) { removed.insert(id); }

/**
 * @brief Schedules a delivery for an object in the scene.
 *
 * @param details JsonObject containing the details of the trip to be scheduled.
 */
/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  WeightDecorator* package = nullptr;

  for (auto& [id, entity] : entities) {
    // std::cout << "name: " << name + "_package" << std::endl;
    // std::cout << "entity->getName(): " << entity->getName() << std::endl;
    if (name + "_package" == entity->getName()) {
      if (WeightDecorator* p = dynamic_cast<WeightDecorator*>(entity)) {
        if (p->requiresDelivery) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    if (package->getWeight() <= 50) {
      scheduledDeliveries.push_back(package);
    } else if (package->getWeight() > 50) {
      scheduledDeliveriesOver50.push_back(package);
    }
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

/**
 * @brief Retrieves the graph used in the simulation.
 *
 * @return Pointer to the IGraph object representing the graph used in the
 * simulation.
 */
const routing::IGraph* SimulationModel::getGraph() { return graph; }

/**
 * @brief Updates the simulation.
 *
 * This method updates each entity and the controller based on the time delta.
 *
 * @param dt The time delta in seconds.
 */
/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

/**
 * @brief Stops the simulation.
 */
void SimulationModel::stop(void) { controller.stop(); }

/**
 * @brief Removes an entity from the simulation by its ID.
 *
 * This is an internal method used to handle the removal process of entities.
 *
 * @param id The ID of the entity to remove.
 */
void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}
