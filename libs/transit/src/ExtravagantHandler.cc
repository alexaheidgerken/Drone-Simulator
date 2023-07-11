#include "ExtravagantHandler.h"

void ExtravagantHandler::Handle(
    IEntity* entity, std::vector<IEntity*> scheduler,
    double dt) {  // needs decorated IEntities to be passed
  JsonObject details = entity->GetDetails();
  std::string type = details["type"];
  std::string travelType = details["travelType"];

  if (type == "drone" &&
      travelType == "extravagant") {  // replacement for Drone::GetNearestEntity
                                      // if entity is drone and available
    if (entity->GetAvailability()) {
      IEntity* currentRider = nullptr;

      for (auto rider : scheduler) {
        JsonObject riderDetails = rider->GetDetails();
        std::string riderType = riderDetails["travelType"];
        if (rider->GetAvailability() &&
            riderType ==
                "extravagant") {  // if rider is available and extravagant
          currentRider = rider;
          entity->SetNearestEntity(rider);
          break;
        }
      }

      if (currentRider) {
        currentRider->SetAvailability(false);
        entity->SetAvailability(false);
        entity->SetPickedUp(false);

        entity->SetDestination(currentRider->GetPosition());
        Vector3 finalDest = currentRider->GetDestination();

        entity->SetToRobot("dijkstra", entity->GetPosition(),
                           currentRider->GetPosition());

        std::string strat = currentRider->GetStrategyName();
        entity->SetToDestination(strat, entity->GetDestination(), finalDest);
      }
    }

    entity->Update(dt, scheduler);
  } else {
    AbstractHandler::Handle(entity, scheduler, dt);
  }
}
