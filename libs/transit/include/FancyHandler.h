#ifndef FANCY_HANDLER_H_
#define FANCY_HANDLER_H_

#include "AbstractHandler.h"

/**
 * @brief this class handles rides with fancy entities
 */
class FancyHandler : public AbstractHandler {
 public:
  /**
   * @brief Handle the entity
   * @param entity The entity to handle
   * @param scheduler The scheduler containing other entities
   * @param dt The time step
   */
  void Handle(IEntity* entity, std::vector<IEntity*> scheduler,
              double dt) override;
};

#endif  // FANCY_HANDLER_H_
