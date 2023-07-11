#ifndef STANDARD_HANDLER_H_
#define STANDARD_HANDLER_H_

#include "AbstractHandler.h"

/**
 * @brief This class handles rides with standard entities
 */
class StandardHandler : public AbstractHandler {
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

#endif  // STANDARD_HANDLER_H_
