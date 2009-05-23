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

DiscreteSimulator::DiscreteSimulator(SensorNetwork * sensorNetwork) : sensorNetwork(sensorNetwork), _currentTime(0),running(false) {

  nodes = QVector<Node::DiscreteSim *>::fromStdVector (sensorNetwork->getSimNodePointers()); /* FIXME, still deciding whether this should be a class variable or not*/ 
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
  
  for (int phase = 0 ; phase < Node::DiscreteSim::numberOfPhases ; phase++)
    for (int n = 0 ; n < nodes.size() ; n++)
      nodes[n]->doNextPhaseOfTimeStep();
    
  emit finishedTimeStep ();
}



/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::requestStopRunning() {
  running = false;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSimulator::run() {

  speed = 10; /* ms/s */
  stepsToRun = 10; /* ms */
  running = true;
  while(running) {
  
    control.lock();
  
    
    if (stepsToRun > 0) {
      sleep(1);
      incrementTimeStep();
      stepsToRun--;
    }
    
    control.unlock();
  }

}


} /* end of namespace Simulator */


} /* end of namespace WSN */













