#include "ExtravagantDecorator.h"

JsonObject ExtravagantDecorator::GetDetails() const {
  JsonObject details = this->entity->GetDetails();
  details["travelType"] = "extravagant";
  return details;
}
