#include "SimulationModel.h"

#include "DroneFactory.h"
#include "ExtravagantDecorator.h"
#include "FancyDecorator.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "RobotFactory.h"
#include "StandardDecorator.h"
#include "TypeDecorator.h"
#include "UfoFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new UfoFactory());
  standardHandler = new StandardHandler();
  fancyHandler = new FancyHandler();
  extravagantHandler = new ExtravagantHandler();
  standardHandler->SetNext(fancyHandler)
      ->SetNext(extravagantHandler);  // set up the chain of responsibility
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  delete graph;
  delete compFactory;
  delete standardHandler;
  delete fancyHandler;
  delete extravagantHandler;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);
  IEntity* decoratedEntity;
  // get random int between 1 and 3
  int wrapType = myNewEntity->GetId() % 3 + 1;

  // wrap the entity with a decorator
  //  keep even amount of each decorator by using ID % 3
  if (wrapType == 1) {
    decoratedEntity = new StandardDecorator(myNewEntity);
  } else if (wrapType == 3) {  // 3 bc decorating also increments id
    decoratedEntity = new FancyDecorator(myNewEntity);
  } else {
    decoratedEntity = new ExtravagantDecorator(myNewEntity);
  }

  // Call AddEntity to add it to the view
  DataCollection* dataCollection = DataCollection::GetInstance();
  dataCollection->EntityCreation(decoratedEntity->GetDetails());
  controller.AddEntity(*decoratedEntity);
  entities.push_back(decoratedEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  std::string droneReq = details["droneReq"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;
  IEntity* decoratedEntity;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    // std::string wrapper = entity->GetType();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      if (droneReq.compare("standard") == 0) {
        decoratedEntity = new StandardDecorator(entity);
      }
      if (droneReq.compare("fancy") == 0) {
        decoratedEntity = new FancyDecorator(entity);
      }
      if (droneReq.compare("extravagant") == 0) {
        decoratedEntity = new ExtravagantDecorator(entity);
      }
      scheduler.push_back(decoratedEntity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    standardHandler->Handle(entities[i], scheduler, dt);
    // entities[i]->Update(dt, scheduler);

    // Update the position in the data collection
    DataCollection* dataCollection = DataCollection::GetInstance();
    JsonObject details = entities[i]->GetDetails();
    controller.UpdateEntity(*entities[i]);
    dataCollection->UpdatePosition(entities[i], dt);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}

void SimulationModel::ToCSV() { DataCollection::GetInstance()->ToCSV(); }
