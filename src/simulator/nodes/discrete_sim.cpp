
#include "discrete_sim.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Nodes
{

  
/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim::DiscreteSim(Type type, int id, double x, double y, Node::State state) : Node(id,x,y,state), type(type), otherNode(0) {
}
  
/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim::~DiscreteSim() {
}
  
/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::setState(Node::State state){
  Node::setState(state);
}

/****************************************************************************
**
** Author: Richard Baxter
**
** calls this node to perform a specific phase of it's execution
**
****************************************************************************/

void DiscreteSim::doTimeStep(int phase) {
  
        if (phase == 0) stateSetupPhase();
  else  if (phase == 1) hardwareSimPhase();
  else  if (phase == 2) stateUpdatePhase();

}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateSetupPhase() {
  nextState = _state;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


void DiscreteSim::hardwareSimPhase() {

  if (energyRemaining <= 0) {
    nextState = Node::OutOfEnergy;
    return;
  }
  //else

  switch (_state) {
  //-------------------------------------------------------------------------------
  
  case Node::ReadyToSend :
    nextState = Node::Sending;
    
    otherNode = (DiscreteSim*)getNextHop();
    otherNode->nextState = Node::Receiving;
    otherNode->otherNode = this;
    
    
    std::cout << id <<" State == ReadyToSend, sending to " << otherNode->getId() << std::endl;
    //qDebug() << node;
    //qDebug() << node->id;
    //qDebug() << node->otherNode;
    //qDebug() << node->otherNode->id;
    sendReceiveTimer = 5; // 30 ms, TODO make time based on bandwidth and packet length
    //emit logEvent(QString("Node %1 sending packet to Node %2").arg(id).arg(otherNode->id));
    
    //emit logEvent(QString("node id %1 state %2").arg(id).arg(state));
    
    break;
  //-------------------------------------------------------------------------------
  case Node::Sending : 
    //emit logEvent(QString("node id %1 state %2 timer = %3").arg(id).arg(state).arg(sendReceiveTimer));
    if (sendReceiveTimer)
      sendReceiveTimer--;
    else
    {
      //finished sending
      nextState = Node::Idle;
      
      
      otherNode->nextState = Node::ReadyToSend; /* the other node is now ready to send */
    }
  
    break;
  //-------------------------------------------------------------------------------
  case Node::Receiving :
  
    std::cout << id <<" State == Receiving, recieving from " << otherNode->getId() << std::endl;
  
    break;
  //-------------------------------------------------------------------------------
  case Node::OutOfEnergy :
    // it's dead - this should never be reasched because of the exit condition at the top of the function
    break;
  //-------------------------------------------------------------------------------
    
  default:
    //ERROR
    break;
    
  }

}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateUpdatePhase() {
  _state = nextState;
}




} /* end of namespace Nodes */

} /* end of namespace Simulator */


} /* end of namespace WSN */

