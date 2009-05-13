#include "discrete_simulator.h"


namespace WSN
{

namespace Simulator
{


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSimulator::DiscreteSimulator(SensorNetwork * sensorNetwork) : sensorNetwork(sensorNetwork), _currentTime(0) {

}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSimulator::~DiscreteSimulator() {


}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

unsigned long DiscreteSimulator::currentTime() {
  return _currentTime;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::incrementTimeStep() {

  _currentTime++;
  
  std::vector <Node>& nodes = sensorNetwork->nodes;

  for (int i = 0 ; i < nodes.size() ; i++)
    incrementTimeStep(nodes[i]);
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::incrementTimeStep(Node & node) {
  

}


} /* end of namespace Simulator */


} /* end of namespace WSN */
