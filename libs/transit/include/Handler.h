#ifndef HANDLER_H_
#define HANDLER_H_

#include "IEntity.h"

/**
 * @brief this class is the base class for the handler classes
 */
class Handler {
 public:
  /**
   * @brief Set the Next handler object in chain
   * @param handler
   * @return Handler* for chaining calls
   */
  virtual Handler* SetNext(Handler* handler) = 0;
  /**
   * @brief Handle the entity
   * @param entity The entity to handle
   * @param scheduler The scheduler containing other entities
   * @param dt The time step
   */
  virtual void Handle(IEntity* entity, std::vector<IEntity*> scheduler,
                      double dt) = 0;
};

#endif  // HANDLER_H_
