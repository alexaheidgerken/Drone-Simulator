#ifndef ABSTRACT_HANDLER_H_
#define ABSTRACT_HANDLER_H_

#include "Handler.h"

/**
 * @brief This class inherits from the Handler class and is an abstract
 * handler that will be used to chain handlers together.
 */
class AbstractHandler : public Handler {
 public:
  /**
   * @brief Construct a new Abstract Handler object
   */
  AbstractHandler() : nextHandler(nullptr) {}
  /**
   * @brief Set the Next object
   * @param handler
   * @return Handler* for chaining calls
   */
  Handler* SetNext(Handler* handler) override {
    this->nextHandler = handler;
    return handler;
  }
  /**
   * @brief Handle the entity
   * @param entity The entity to handle
   * @param scheduler The scheduler containing other entities
   * @param dt The time step
   */
  void Handle(IEntity* entity, std::vector<IEntity*> scheduler,
              double dt) override {
    if (this->nextHandler) {
      this->nextHandler->Handle(entity, scheduler, dt);
    }
    entity->Update(dt, scheduler);
  }

 protected:
  Handler* nextHandler = nullptr;
};

#endif  // ABSTRACT_HANDLER_H_
