#include "StandardDecorator.h"

JsonObject StandardDecorator::GetDetails() const {
  JsonObject details = this->entity->GetDetails();
  details["travelType"] = "standard";
  return details;
}
