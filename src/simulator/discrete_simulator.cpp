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

  // assuming that the next state will remain unchanged
  for (int i = 0 ; i < nodes.size() ; i++)
    nodes[i].nextState = nodes[i].state;
    
  // simulating node hardware
  for (int i = 0 ; i < nodes.size() ; i++)
    incrementTimeStep(nodes[i]);
  
  //updating states
  for (int i = 0 ; i < nodes.size() ; i++)
    nodes[i].state = nodes[i].nextState;
    
  timeStepCompleted();
}


void DiscreteSimulator::timeStepCompleted() {
  
  if (sensorNetwork->baseStation.state == Node::READY_TO_SEND)
  ;
  
}

/****************************************************************************
**
** Author: Richard Baxter
**
** Hardware of what the nodes actually do is simulated here
**
****************************************************************************/

/* NOTE don't set state in the nodes here, only nextState*/
void DiscreteSimulator::incrementTimeStep(Node & node) {

  if (node.energyRemaining <= 0) {
    node.nextState = Node::OUT_OF_ENERGY;
    return;
  }
  //else

  switch (node.state) {
  //-------------------------------------------------------------------------------
  
  case Node::READY_TO_SEND :
    node.state = Node::SENDING;
    node.otherNode = sensorNetwork->getNode(node.getNextHop());
    node.timer = 30; // 30 ms, TODO make time based on bandwidth and packet length
    
    break;
  //-------------------------------------------------------------------------------
  case Node::SENDING : 
    if (node.timer)
      node.timer--;
    else
    {
      //finished sending
      node.nextState = Node::IDLE;
      
      
      node.otherNode->nextState = Node::READY_TO_SEND; /* the other node is now ready to send */
    }
  
    break;
  //-------------------------------------------------------------------------------
  case Node::RECEIVING :
  
  
    break;
  //-------------------------------------------------------------------------------
  case Node::OUT_OF_ENERGY :
    // it's dead - this should never be reasched because of the exit condition at the top of the function
    break;
  //-------------------------------------------------------------------------------
    
  default:
    //ERROR
    break;
    
  }

}


} /* end of namespace Simulator */


} /* end of namespace WSN */













