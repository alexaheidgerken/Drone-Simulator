#ifndef _DATA_COLLECTION_H_
#define _DATA_COLLECTION_H_

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @brief DataCollection class using Singleton Pattern
 */
class DataCollection {
 protected:
  DataCollection() {}

  static DataCollection* instance;

  // maps entity name to a map of key-value pairs
  std::map<std::string, std::map<std::string, std::string>> entityData;

  std::map<std::string, std::map<std::string, Vector3>> entityCoordinates;
  // entityData will hold string data
  // entityCoordinates will hold positional data

 public:
  /**
   * @brief Make sure the class is not cloneable
   */
  DataCollection(DataCollection const&) = delete;
  /**
   * @brief Make sure that the class is not assignable
   */
  void operator=(DataCollection const&) = delete;

  /**
   * @brief Destructor
   */
  ~DataCollection() {}

  /**
   * @brief Update the position of the entity in the data collection
   * @param entity The entity to update
   * @param dt The time step for the simulation
   */
  void UpdatePosition(const IEntity* entity, double dt);

  /**
   * @brief Get the DataCollection instance
   * @return DataCollection*
   */
  static DataCollection* GetInstance();

  /**
   * @brief Write the data to a CSV file
   * @param dt current time step for the simulation
   */
  void ToCSV();

  /**
   * @brief Write/Update a key-value pair to the data collection
   * @param details The JsonObject containing the key-value pairs
   */
  void EntityCreation(const JsonObject& details);
};

#endif  // _DATA_COLLECTION_H_
