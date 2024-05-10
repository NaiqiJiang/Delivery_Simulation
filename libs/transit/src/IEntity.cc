#include "IEntity.h"

/**
 * @brief Default constructor for IEntity.
 *
 * Initializes a new IEntity with a unique ID.
 */
IEntity::IEntity() {
  static int currentId = 0;
  id = currentId;
  currentId++;
}

/**
 * @brief Constructs an IEntity object with JSON configuration details.
 *
 * Initializes an IEntity with properties specified in a JSON object. This
 * includes position, direction, color, name, and speed.
 *
 * @param details JSON object containing configuration data.
 */
IEntity::IEntity(JsonObject& details) : IEntity() {
  this->details = details;
  JsonArray pos(details["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(details["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  if (details.contains("color")) {
    std::string col = details["color"];
    color = col;
  }
  std::string n = details["name"];
  name = n;
  // std::cout << "IEntityName: " << name << std::endl;
  speed = details["speed"];
}

/**
 * @brief Destroy the IEntity object.
 */
IEntity::~IEntity() {}

/**
 * @brief Link the IEntity to a simulation model.
 *
 * @param model Pointer to the SimulationModel.
 */
void IEntity::linkModel(SimulationModel* model) { this->model = model; }

/**
 * @brief Get the current id of the entity.
 *
 * @return Vector3 representing the current id of the entity.
 */
int IEntity::getId() const { return id; }

/**
 * @brief Get the current position of the entity.
 *
 * @return Vector3 representing the current position of the entity.
 */
Vector3 IEntity::getPosition() const { return position; }

/**
 * @brief Get the current direction of the entity.
 *
 * @return Vector3 representing the current direction of the entity.
 */
Vector3 IEntity::getDirection() const { return direction; }

/**
 * @brief Get the current details of the entity.
 *
 * @return Vector3 representing the current details of the entity.
 */
const JsonObject& IEntity::getDetails() const { return details; }

/**
 * @brief Get the current color of the entity.
 *
 * @return Vector3 representing the current color of the entity.
 */
std::string IEntity::getColor() const { return color; }

/**
 * @brief Get the current name of the entity.
 *
 * @return Vector3 representing the current name of the entity.
 */
std::string IEntity::getName() const { return name; }

/**
 * @brief Get the current speed of the entity.
 *
 * @return Vector3 representing the current speed of the entity.
 */
double IEntity::getSpeed() const { return speed; }

/**
 * @brief Set the position of the entity.
 *
 * @param pos_ Vector3 representing the new position of the entity.
 */
void IEntity::setPosition(Vector3 pos_) { position = pos_; }

/**
 * @brief Set the direction of the entity.
 *
 * @param pos_ Vector3 representing the new direction of the entity.
 */
void IEntity::setDirection(Vector3 dir_) { direction = dir_; }

/**
 * @brief Set the color of the entity.
 *
 * @param pos_ Vector3 representing the new color of the entity.
 */
void IEntity::setColor(std::string col_) { color = col_; }

/**
 * @brief Rotate the entity by a specified angle.
 *
 * This method rotates the direction of the entity around the y-axis by the
 * given angle.
 *
 * @param angle Angle in radians to rotate the entity.
 */
void IEntity::rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
