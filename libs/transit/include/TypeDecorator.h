#ifndef TYPE_DECORATOR_H_
#define TYPE_DECORATOR_H_

#include "Drone.h"
#include "IEntity.h"
#include "IStrategy.h"
/**
 * @brief this class inherits from the IEntity class and is represents
 * a type decorator where the entity will have a travel type.
 */
class TypeDecorator : public IEntity {
 protected:
  /**
   * @brief the entity to decorate onto
   */
  IEntity* entity;

 public:
  /**
   * @brief Construct a new Type Decorator object
   *
   * @param entity the entity to decorate onto
   */
  TypeDecorator(IEntity* entity) { this->entity = entity; }

  /**
   * @brief Type Decorator Destructor
   */
  ~TypeDecorator() {
    delete this->entity;
    delete this->graph;
  }

  /**
   * @brief Get the decorated Details object
   *
   * @return JsonObject
   */
  JsonObject GetDetails() const override {}

  /**
   * @brief Update the entity's position and direction
   * @param dt Time step
   * @param scheduler Vector containing entities
   */
  void Update(double dt, std::vector<IEntity*> scheduler) {
    this->entity->Update(dt, scheduler);
  }
  /**
   * @brief Get the Id of the entity
   * @return int
   */
  int GetId() const override { return this->entity->GetId(); }

  /**
   * @brief Get the position of the entity
   * @return Vector3
   */
  Vector3 GetPosition() const override { return this->entity->GetPosition(); }
  /**
   * @brief Get the direction of the entity
   * @return Vector3
   */
  Vector3 GetDirection() const override { return this->entity->GetDirection(); }
  /**
   * @brief Get the destination of the entity
   * @return Vector3
   */
  Vector3 GetDestination() const override {
    return this->entity->GetDestination();
  }
  /**
   * @brief Get the color of the entity
   * @return std::string
   */
  std::string GetColor() const override { return this->entity->GetColor(); }
  /**
   * @brief Get the speed of the entity
   * @return float
   */
  float GetSpeed() const override { return this->entity->GetSpeed(); }
  /**
   * @brief Get the Strategy Name of the entity
   * @return std::string
   */
  std::string GetStrategyName() const override {
    return this->entity->GetStrategyName();
  }
  /**
   * @brief Get the availability of the entity
   * @return bool
   */
  bool GetAvailability() const override {
    return this->entity->GetAvailability();
  }
  /**
   * @brief Set the strategy name of the entity
   * @param strategyName_  Strategy name
   */
  void SetStrategyName(std::string strategyName_) override {
    this->entity->SetStrategyName(strategyName_);
  }
  /**
   * @brief Set the availability of the entity
   * @param choice  The desired availability of the entity
   */
  void SetAvailability(bool choice) override {
    this->entity->SetAvailability(choice);
  }
  /**
   * @brief Set the graph of the entity
   * @param graph  The graph to set
   */
  void SetGraph(const IGraph* graph) { this->entity->SetGraph(graph); }
  /**
   * @brief Set the Position of the entity
   *
   * @param pos_ Vector3 containing the position
   */
  void SetPosition(Vector3 pos_) { this->entity->SetPosition(pos_); }
  /**
   * @brief Set the Direction of the entity
   * @param dir_ Vector3 containing the direction
   */
  void SetDirection(Vector3 dir_) { this->entity->SetDirection(dir_); }
  /**
   * @brief Set the Destination of the entity
   * @param des_ Vector3 containing the destination
   */
  void SetDestination(Vector3 des_) { this->entity->SetDestination(des_); }
  /**
   * @brief Set the coloe of the entity
   * @param col_ std::string containing the color
   */
  void SetColor(std::string col_) { this->entity->SetColor(col_); }
  /**
   * @brief Set the picked up status of the entity
   * @param pickedUp bool containing the picked up status
   */
  void SetPickedUp(bool pickedUp) { this->entity->SetPickedUp(pickedUp); }
  /**
   * @brief Set the To Robot strategy of the entity
   * @param strategyName string containing the strategy name
   * @param start Vector3 containing the start position
   * @param end vector3 containing the end position
   */
  void SetToRobot(std::string strategyName, Vector3 start, Vector3 end) {
    this->entity->SetToRobot(strategyName, start, end);
  }
  /**
   * @brief Set the To Destination strategy of the entity
   * @param strategyName string containing the strategy name
   * @param start Vector3 containing the start position
   * @param end vector3 containing the end position
   */
  void SetToDestination(std::string strategyName, Vector3 start, Vector3 end) {
    this->entity->SetToDestination(strategyName, start, end);
  }
  /**
   * @brief Set the Nearest Entity object
   * @param entity
   */
  void SetNearestEntity(IEntity* entity) {
    this->entity->SetNearestEntity(entity);
  }
  /**
   * @brief Rotate the entity
   * @param angle
   */
  void Rotate(double angle) { this->entity->Rotate(angle); }
  /**
   * @brief Jump the entity
   * @param height height to jump
   */
  void Jump(double height) { this->entity->Jump(height); }
};

#endif  // TYPE_DECORATOR_H_
