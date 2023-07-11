#include "UfoFactory.h"

IEntity* UfoFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("ufo") == 0) {
    std::cout << "UFO Created" << std::endl;
    return new Ufo(entity);
  }
  return nullptr;
}
