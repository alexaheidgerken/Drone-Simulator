#include "FancyDecorator.h"

JsonObject FancyDecorator::GetDetails() const {
  JsonObject details = this->entity->GetDetails();
  details["travelType"] = "fancy";
  return details;
}
