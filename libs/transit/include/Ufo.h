#ifndef _UFO_H_
#define _UFO_H_

#include <random>

#include "IEntity.h"

/**
 * @class Ufo
 * @brief Represents a UFO in the drone simulation.
 */
class Ufo : public IEntity {
 public:
  /**
   * @brief UFOs are created with a JSON object
   * @param obj JSON object containing the UFO's information
   */
  Ufo(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Ufo();

  /**
   * @brief Updates the UFO's position based on its speed and direction
   * @param dt The change in time
   * @param scheduler The scheduler containing all the entities
   */
  void Update(double dt, std::vector<IEntity*> scheduler) override;

  /**
   * @brief Sets a new random destination for the UFO
   */
  void SetDestination(Vector3 des_);

  /**
   * @brief Gets the UFO's position
   * @return The UFO's position
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the UFO's direction
   * @return The UFO's direction
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the UFO's destination
   * @return The UFO's destination
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the UFO's details
   * @return The UFO's details
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the UFO's speed
   * @return The UFO's speed
   */
  float GetSpeed() const { return speed; }

 private:
  float speed;
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
};

#endif  // _UFO_H_
