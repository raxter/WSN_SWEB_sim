
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

DiscreteSim::DiscreteSim(Type type, int id, double x, double y, Node::State state) : Node(id,x,y,state), energyRemaining(100), type(type), otherNode(0), packet(0), phase(-1) {
}
  
/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim::~DiscreteSim() {
  if (packet)
    delete packet; /* in case program is exited in the middle of simulation and it needs to be cleaned up*/
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

const DiscreteSim * DiscreteSim::getOtherNode() const {
  return (DiscreteSim *)otherNode;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

const Packet * DiscreteSim::getPacket() const {
  return packet;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double DiscreteSim::getPercentageDone() const {
  return sendTimerTotal == -1?-1:(double)(sendTimer)/(sendTimerTotal);
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::setState(Node::State state) {
  /* if during the setup of execute phase, use the nextState*/
  if (phase == 1|| phase == 0) {
    nextState = state;
  }
  else /*otherwise if in the reset/update phase or not in the middle of simulation use the normal set menthod*/
    Node::setState(state);
}

/****************************************************************************
**
** Author: Richard Baxter
**
** calls this node to perform a specific phase of it's execution
**
****************************************************************************/

void DiscreteSim::doNextPhaseOfTimeStep() {

  this->phase++;
  
        if (phase == 0) stateSetupPhase();
  else  if (phase == 1) hardwareSimPhase();
  else  if (phase == 2) { stateUpdatePhase(); phase = -1;}
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateSetupPhase() {
  setState(state());
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


void DiscreteSim::hardwareSimPhase() {

  switch (state()) {
  case Node::ReadyToSend :  stateReadyToSend();   break;
  case Node::Sending :      stateSending();       break;
  case Node::Receiving :    stateReceiving();     break;
  case Node::OutOfEnergy :  stateOutOfEnergy();   break;
  case Node::Idle :         stateIdle();          break;
  
  default:
    //ERROR
    break;
    
  }
  
  if (energyRemaining <= 0) {
    nextState = Node::OutOfEnergy;
  }

}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateUpdatePhase() {
  setState(nextState);
}



/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateIdle() {
  /* do nothing */
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateSending(){
  //std::cout << id <<" State == Sending" << std::endl;
  //std::cout <<  "sending to " << otherNode->getId() << std::endl;
  if (sendTimer)
    sendTimer--;
  else
  {
    sendTimerTotal = -1;
    packetSendFinish();
  }
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::stateReceiving(){
  //std::cout << id <<" State == Receiving" << std::endl;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


void DiscreteSim::stateReadyToSend(){

    //std::cout << id <<" State == ReadyToSend, sending Packet" << std::endl;
    packetSendStart();
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


void DiscreteSim::stateOutOfEnergy(){
  /*do nothing*/
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::packetReceiveStart(){

  setState(Node::Receiving); /* the other node is now ready to send */
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void DiscreteSim::packetReceiveFinished(Packet * packet){
  
  this->packet = packet; //FIXME multiple received packets will overwite eachother!
  setState(Node::ReadyToSend);
}

/****************************************************************************
**
** Author: Richard Baxter
**
** assumes that packet is not NULL
**
****************************************************************************/
    
void DiscreteSim::packetSendStart() {
  //std::cout << "DiscreteSim::packetSendStart()" << std::endl;
  setState(Node::Sending);
  
  otherNode = (DiscreteSim*)getNextHop();
  
  sendTimerTotal = 5-1; // in ms, TODO make time based on bandwidth and packet length
  sendTimer = sendTimerTotal;
  
  otherNode->packetReceiveStart();
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/
    
void DiscreteSim::packetSendFinish() {
  
  setState(Node::Idle);
  otherNode->packetReceiveFinished(packet);
  packet = NULL;
}
    



} /* end of namespace Nodes */

} /* end of namespace Simulator */


} /* end of namespace WSN */

