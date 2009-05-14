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

  nodes = QVector<Node *>::fromStdVector (sensorNetwork->getNodePointers()); /* FIXME, still deciding whether this should be a class variable or not*/ 
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
  for (int i = 0 ; i < nodes.size() ; i++)
    nodes[i]->nextState = nodes[i]->state;
    
  // simulating node hardware
  for (int i = 0 ; i < nodes.size() ; i++)
    incrementTimeStep(nodes[i]);
  
  //updating states
  for (int i = 0 ; i < nodes.size() ; i++)
    nodes[i]->state = nodes[i]->nextState;
    
  timeStepCompleted();
  emit finishedTimeStep ();
}

/* should this be in the simulator class as round complete or check base station or something*/
void DiscreteSimulator::timeStepCompleted() {
  
  if (nodes[0]->state == Node::READY_TO_SEND) /* checking the baseStation state*/
  
    /*TODO, ask it to send the next signal*/;
  
}

/****************************************************************************
**
** Author: Richard Baxter
**
** Hardware of what the nodes actually do is simulated here
**
****************************************************************************/

/* NOTE don't set state in the nodes here, only nextState*/
void DiscreteSimulator::incrementTimeStep(Node * node) {
  

  if (node->energyRemaining <= 0) {
    node->nextState = Node::OUT_OF_ENERGY;
    return;
  }
  //else

  switch (node->state) {
  //-------------------------------------------------------------------------------
  
  case Node::READY_TO_SEND :
    node->nextState = Node::SENDING;
    node->otherNode = sensorNetwork->getNode(node->getNextHop());
    node->sendReceiveTimer = 5; // 30 ms, TODO make time based on bandwidth and packet length
    emit logEvent(QString("Node %1 sending packet to Node %2").arg(node->id).arg(node->otherNode->id));
    
    emit logEvent(QString("node id %1 state %2").arg(node->id).arg(node->state));
    
    break;
  //-------------------------------------------------------------------------------
  case Node::SENDING : 
    emit logEvent(QString("node id %1 state %2 timer = %3").arg(node->id).arg(node->state).arg(node->sendReceiveTimer));
    if (node->sendReceiveTimer)
      node->sendReceiveTimer--;
    else
    {
      //finished sending
      node->nextState = Node::IDLE;
      
      
      node->otherNode->nextState = Node::READY_TO_SEND; /* the other node is now ready to send */
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













