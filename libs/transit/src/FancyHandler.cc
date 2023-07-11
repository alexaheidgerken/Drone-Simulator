#include "FancyHandler.h"

void FancyHandler::Handle(IEntity* entity, std::vector<IEntity*> scheduler,
                          double dt) {
  JsonObject details = entity->GetDetails();
  std::string type = details["type"];
  std::string travelType = details["travelType"];

  if (type == "drone" &&
      travelType == "fancy") {  // replacement for Drone::GetNearestEntity if
                                // entity is drone and available
    if (entity->GetAvailability()) {
      IEntity* currentRider = nullptr;

      for (auto rider : scheduler) {
        JsonObject riderDetails = rider->GetDetails();
        std::string riderType = riderDetails["travelType"];
        if (rider->GetAvailability() &&
            riderType == "fancy") {  // if rider is available and fancy
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

        entity->SetToRobot("dfs", entity->GetPosition(),
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
