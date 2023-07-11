#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "AbstractHandler.h"
#include "CompositeFactory.h"
#include "DataCollection.h"
#include "Drone.h"
#include "ExtravagantDecorator.h"
#include "ExtravagantHandler.h"
#include "FancyDecorator.h"
#include "FancyHandler.h"
#include "Handler.h"
#include "IController.h"
#include "IEntity.h"
#include "Robot.h"
#include "StandardDecorator.h"
#include "StandardHandler.h"
#include "TypeDecorator.h"
#include "graph.h"

using namespace routing;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Creates a new simulation entitiy
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entnity to create
   **/
  void CreateEntity(JsonObject& entity);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void ScheduleTrip(JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void Update(double dt);

  // Adds a new factory
  /**
   * @brief Add new factory into the simulation
   * @param factory - Factory to add into the simulation.
   */
  void AddFactory(IEntityFactory* factory);

  /**
   * @brief Convert the simulation data to CSV using DataCollection
   */
  void ToCSV();

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> scheduler;
  const IGraph* graph;
  CompositeFactory* compFactory;
  // handlers
  Handler* standardHandler;
  Handler* fancyHandler;
  Handler* extravagantHandler;
  // data collection
  DataCollection* dataCollection;
};

#endif
