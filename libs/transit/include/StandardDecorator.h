#ifndef STANDARD_DECORATOR_H_
#define STANDARD_DECORATOR_H_

#include "IEntity.h"
#include "TypeDecorator.h"

/**
 * @brief this class  is the decorator for a standard entity
 */
class StandardDecorator : public TypeDecorator {
 public:
  /**
   * @brief Construct a new Standard Decorator object
   *
   * @param entity the entity to decorate onto
   */
  StandardDecorator(IEntity* entity) : TypeDecorator(entity) {}

  /**
   * @brief Standard Decorator Destructor
   */
  ~StandardDecorator() {
    delete this->entity;
    delete this->graph;
  }

  /**
   * @brief Get the decorated Details object
   *
   * @return JsonObject
   */
  JsonObject GetDetails() const override;
};

#endif  // STANDARD_DECORATOR_H_
