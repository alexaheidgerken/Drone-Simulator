#include "Ufo.h"

Ufo::Ufo(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  // randomly set destination on creation
  SetDestination(Vector3(0, 0, 0));
}

Ufo::~Ufo() { delete graph; }

void Ufo::Update(double dt, std::vector<IEntity*> scheduler) {
  // check if destination is reached, if it is, set new destination
  if (position.Distance(destination) < 1) {
    SetDestination(Vector3(0, 0, 0));
  }
  // update direction
  direction = (destination - position).Unit();
  // update position
  position = position + direction * speed * dt;
}

void Ufo::SetDestination(Vector3 des_) {
  // set random destination within these bounds:
  // x: [-1400, 1500], y: [400, inf], z: [-800, 800]
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> disX(-1400, 1500);
  std::uniform_real_distribution<> disY(400, 1000);
  std::uniform_real_distribution<> disZ(-800, 800);

  destination = {disX(gen), disY(gen), disZ(gen)};
}
