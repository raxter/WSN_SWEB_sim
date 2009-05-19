#include "discrete_simulator.h"


#include <QDebug>

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

  nodes = QVector<Nodes::DiscreteSim *>::fromStdVector (sensorNetwork->getSimNodePointers()); /* FIXME, still deciding whether this should be a class variable or not*/ 
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

   emit logEvent(QString("incrementTimeStep()"));
  _currentTime++;

  // assuming that the next state will remain unchanged
  //for (int i = 0 ; i < nodes.size() ; i++)
  //  nodes[i]->nextState = nodes[i]->state;
    
  // simulating node hardware
  
  for (int phase = 0 ; phase < Nodes::DiscreteSim::numberOfPhases ; phase++)
    for (int n = 0 ; n < nodes.size() ; n++)
      nodes[n]->doTimeStep(phase);
    
  emit finishedTimeStep ();
}



} /* end of namespace Simulator */


} /* end of namespace WSN */













