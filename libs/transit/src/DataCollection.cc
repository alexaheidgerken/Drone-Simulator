#include "DataCollection.h"

DataCollection* DataCollection::instance = nullptr;

DataCollection* DataCollection::GetInstance() {
  if (instance == nullptr) {
    instance = new DataCollection();
  }
  return instance;
}

void DataCollection::UpdatePosition(const IEntity* entity, double dt) {
  JsonObject details = entity->GetDetails();
  std::string entityName = details["name"];

  float dis =
      entityCoordinates[entityName]["position"].Distance(entity->GetPosition());
  float cur_dis = std::stof(entityData[entityName]["distance"]);

  entityData[entityName]["distance"] = std::to_string(cur_dis + dis);
  entityCoordinates[entityName]["position"] = entity->GetPosition();

  entityCoordinates[entityName]["direction"] = entity->GetDirection();
  entityCoordinates[entityName]["destination"] = entity->GetDestination();

  float cur_time = std::stof(entityData[entityName]["time"]);
  entityData[entityName]["time"] = std::to_string(dt + cur_time);
}

void DataCollection::EntityCreation(
    const JsonObject& details) {  // called when object is created (only once)
  std::string entityName = details["name"];

  std::vector<std::string> keys = {"id", "speed", "travelType", "type"};
  std::vector<std::string> vec_keys = {"position", "direction"};

  for (auto key : keys) {
    entityData[entityName][key] = details[key].ToString();
  }

  for (auto key : vec_keys) {
    JsonArray temp = details[key];
    entityCoordinates[entityName][key] = Vector3(temp[0], temp[1], temp[2]);
  }
  entityData[entityName]["distance"] = "0";
  entityData[entityName]["time"] = "0";
}

void DataCollection::ToCSV() {
  // create new file with name based on current time
  if (!entityData.empty()) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // generate random number 1000-9999
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    int rand_num = dis(gen);

    std::string filename = "./data/save_" + std::to_string(now_time) + "_" +
                           std::to_string(rand_num) + ".csv";
    std::ofstream outFile(filename);

    // Write the keys row (headers)
    // access the nested map of the first entity and write the keys
    std::vector<std::string> keys = {"id",         "speed",     "type",
                                     "travelType", "distance",  "time",
                                     "position",   "direction", "destination"};

    outFile << "name, id, speed, type, travelType, distance, time, position, "
               "direction, destination\n";

    // Write the data rows
    for (auto entity : entityData) {
      outFile << entity.first << ", ";
      for (auto key : keys) {
        if (key == "position" || key == "direction" || key == "destination") {
          std::string name = entity.first;

          Vector3 vec = entityCoordinates[name][key];
          outFile << "[" << vec[0] << "; " << vec[1] << "; " << vec[2] << "]";
          if (key != "destination") {
            outFile << ", ";
          }

        } else {
          outFile << entity.second[key] << ", ";
        }
      }
      outFile << "\n";
    }
    outFile.close();
  }
}
