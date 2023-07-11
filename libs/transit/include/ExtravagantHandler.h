#ifndef EXTRAVAGANT_HANDLER_H_
#define EXTRAVAGANT_HANDLER_H_

#include "AbstractHandler.h"

/**
 * @brief this class handles rides with extravagant entities
 */
class ExtravagantHandler : public AbstractHandler {
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

#endif  // EXTRAVAGANT_HANDLER_H_
