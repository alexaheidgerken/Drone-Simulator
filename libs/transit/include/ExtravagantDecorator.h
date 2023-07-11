#ifndef EXTRAVAGANT_DECORATOR_H_
#define EXTRAVAGANT_DECORATOR_H_

#include "IEntity.h"
#include "TypeDecorator.h"

/**
 * @brief this class  is the decorator for an extravagant entity
 */
class ExtravagantDecorator : public TypeDecorator {
 public:
  /**
   * @brief Construct a new Extravagant Decorator object
   *
   * @param entity the entity to decorate onto
   */
  ExtravagantDecorator(IEntity* entity) : TypeDecorator(entity) {}

  /**
   * @brief Extravagant Decorator Destructor
   */
  ~ExtravagantDecorator() {
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

#endif  // EXTRAVAGANT_DECORATOR_H_
