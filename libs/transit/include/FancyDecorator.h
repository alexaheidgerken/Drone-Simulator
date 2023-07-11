#ifndef FANCY_DECORATOR_H_
#define FANCY_DECORATOR_H_

#include "IEntity.h"
#include "TypeDecorator.h"

/**
 * @brief this class  is the decorator for a fancy entity
 */
class FancyDecorator : public TypeDecorator {
 public:
  /**
   * @brief Construct a new Fancy Decorator object
   *
   * @param entity the entity to decorate onto
   */
  FancyDecorator(IEntity* entity) : TypeDecorator(entity) {}

  /**
   * @brief Fancy Decorator Destructor
   */
  ~FancyDecorator() {
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

#endif  // FANCY_DECORATOR_H_
