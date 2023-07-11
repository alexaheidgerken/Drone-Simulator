#ifndef _UFO_FACTORY_H_
#define _UFO_FACTORY_H_

#include <vector>

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Ufo.h"

/**
 * @brief UFO Factory to produce UFOs.
 *
 */
class UfoFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~UfoFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullptr if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
