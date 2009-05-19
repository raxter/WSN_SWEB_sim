


#include "base_station.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Nodes
{

namespace DiscreteSims
{


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseStation::BaseStation(double x , double y) : DiscreteSim(Nodes::DiscreteSim::BaseStation, -1, x, y), waitingForReply(false)
{
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseStation::~BaseStation()
{

}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void BaseStation::initiate() {
  setState(ReadyToSend);
}



/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void BaseStation::stateIdle() {

  if (!waitingForReply) {
    setState(ReadyToSend);
  }
}

/****************************************************************************
**
** Author: Richard Baxter
**
** overrided method
**
****************************************************************************/

void BaseStation::packetSendStart() {
  packet = new Packet(/*blah blah stuff TODO*/);
  waitingForReply = true;
  DiscreteSim::packetSendStart();
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void BaseStation::packetReceiveFinished(Packet * packet) {
  //DiscreteSim::packetReceiveFinished(NULL);
  delete packet;
  waitingForReply = false;

  setState(Node::ReadyToSend);
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

Node * BaseStation::getNextHop()
{
  /* TODO implement routing for the base station*/
  return targetNode;
}



} /* end of namespace DiscreteSims */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */

