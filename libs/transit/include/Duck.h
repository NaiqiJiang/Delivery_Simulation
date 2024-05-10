#ifndef Duck_H
#define Duck_H

#include <cstdlib>
#include <ctime>
#include <vector>

#include "AstarStrategy.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "SimulationModel.h"
#include "math/vector3.h"

/**
 * @classHDuck
 * @brief Represents aHDuck in a physical system.HDuck move using astar strategy
 */
class Duck : public IEntity {
 public:
  /**
   * @briefHDuck are created with a name
   * @param obj JSON object containing theHDuck's information
   */
  Duck(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Duck();

  /**
   * @brief Updates theHDuck's position
   * @param dt Delta time
   */
  void update(double dt);

 private:
  IStrategy* toFinalDestination = nullptr;
  Vector3 start;
  Vector3 dest;
};

#endif
