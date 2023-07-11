#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
  // CREATE ONE POINTER TO A HANDLER, OTHER 2 WILL BE HELD IN SIMULATION MODEL?
  // DRONES WILL BE CREATED WITH THIS POINTER AND WRAPPED IN A DECORATOR AT
  // CREATION
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  // instead of getting closest entity, we should get the first entity that is
  // available and of the correct type however, to do this we need to have the
  // decorator of this drone, which is not possible in this function

  for (auto entity : scheduler) {  // only robots in scheduler
    // can use decorator of Entity to check if entity is of correct type

    // handler will check if entity is available, its type. If it is, it will
    // perform logic for connecting drone and robot
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }
  // standardHandler.handleRequest(this, entity)
  // ------------------------------- All of this should be done inside
  // handlers-------------------------------

  if (nearestEntity) {
    // set availability to the nearest entity
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();                  // y
    Vector3 finalDestination = nearestEntity->GetDestination();  // y

    toRobot = new BeelineStrategy(position, destination);  // y
    // -----------------------------------------------------

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar")
      toFinalDestination = new JumpDecorator(
          new AstarStrategy(destination, finalDestination, graph));
    else if (strat == "dfs")
      toFinalDestination = new SpinDecorator(new JumpDecorator(
          new DfsStrategy(destination, finalDestination, graph)));
    else if (strat == "dijkstra")
      toFinalDestination = new JumpDecorator(new SpinDecorator(
          new DijkstraStrategy(destination, finalDestination, graph)));
    else
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  /* if (available)
    GetNearestEntity(scheduler); */

  if (toRobot) {
    toRobot->Move(this, dt);

    if (toRobot->IsCompleted()) {
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}

void Drone::SetToRobot(std::string strategyName, Vector3 start, Vector3 end) {
  if (strategyName == "beeline") {
    toRobot = new BeelineStrategy(start, end);
  } else if (strategyName == "astar") {
    toRobot = new AstarStrategy(start, end, graph);
  } else if (strategyName == "dfs") {
    toRobot = new DfsStrategy(start, end, graph);
  } else if (strategyName == "dijkstra") {
    toRobot = new DijkstraStrategy(start, end, graph);
  }
}

void Drone::SetToDestination(std::string strategyName, Vector3 start,
                             Vector3 end) {
  if (strategyName == "beeline") {
    toFinalDestination = new BeelineStrategy(start, end);
  } else if (strategyName == "astar") {
    toFinalDestination =
        new JumpDecorator(new AstarStrategy(start, end, graph));
  } else if (strategyName == "dfs") {
    toFinalDestination = new SpinDecorator(
        new JumpDecorator(new DfsStrategy(start, end, graph)));
  } else if (strategyName == "dijkstra") {
    toFinalDestination = new JumpDecorator(
        new SpinDecorator(new DijkstraStrategy(start, end, graph)));
  }
}
