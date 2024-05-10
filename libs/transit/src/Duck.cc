#include "Duck.h"

/**
 * @brief Constructor for Duck, initializing with a JSON object.
 *
 * Initializes a Duck entity using a JSON object. Inherits initialization
 * from the IEntity class and sets up initial state for the Duck entity.
 *
 * @param obj JSON object used for initialization.
 */
Duck::Duck(JsonObject& obj) : IEntity(obj) {
  // start = this->getPosition();
  // std::srand(std::time(0));
  // double x = -1400 + std::rand() % (1500 - (-1400) + 1);
  // double y = 240 + std::rand() % (300 - 240 + 1);
  // double z = -800 + std::rand() % (800 - (-800) + 1);

  // dest = Vector3(x,y,z);
  // this->toFinalDestination = new AstarStrategy(start, dest,
  // model->getGraph());
}

/**
 * @brief Destructor for Duck.
 *
 * Cleans up resources used by Duck, specifically releasing any
 * dynamic memory allocated for pathfinding strategies.
 */
Duck::~Duck() {
  if (toFinalDestination) delete toFinalDestination;
}

/**
 * @brief Update the state of the Duck.
 *
 * Performs an update on the Duck's state in the game world.
 * It involves pathfinding and movement towards a destination.
 * If the Duck has reached its destination, a new destination
 * is computed and pathfinding towards this new point is initiated.
 *
 * @param dt Delta time, representing the time passed since the last update.
 */
void Duck::update(double dt) {
  if (toFinalDestination == nullptr) {
    start = this->getPosition();
    std::srand(std::time(0));
    double x = -1400 + std::rand() % (1500 - (-1400) + 1);
    double y = 240 + std::rand() % (300 - 240 + 1);
    double z = -800 + std::rand() % (800 - (-800) + 1);

    dest = Vector3(x, y, z);
    this->toFinalDestination =
        new AstarStrategy(start, dest, model->getGraph());
  }
  if (!(toFinalDestination->isCompleted())) {
    toFinalDestination->move(this, dt);
  } else {
    delete toFinalDestination;
    int x = -1400 + std::rand() % (1500 - (-1400) + 1);
    int y = 240 + std::rand() % (300 - 240 + 1);
    int z = -800 + std::rand() % (800 - (-800) + 1);
    start = dest;
    dest = Vector3(x, y, z);
    this->toFinalDestination =
        new AstarStrategy(start, dest, model->getGraph());
  }
}
