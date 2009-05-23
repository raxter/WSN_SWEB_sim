#include "link.h"

#include "simulator/packets/init.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace BaseStationLayers
{


Link::Link() {

  WaitingForGroupInitsToFinish_timeout = 30;
}


Link::~Link(){

}

void Link::proxied_setUpPhase () {
  //std::cout << "in SensorLayers::Link::proxied_setUpPhase ()" << std::endl;
  nextLinkState = currentLinkState;
}


void Link::linkLayerLogic (){
  std::cout << "in BaseStationLayers::Link::linkLayerLogic ()" << std::endl;
  //std::cout << currentLinkState << std::endl;
  //std::cout << Uninitialised << std::endl;
  if (currentLinkState == LinkUninitialised) {
    for (int i = 0 ; i < DiscreteSim::numberOfSectors ; i++) {
    
      BasePacket* toSend = new Packet::Init(500, *this, i, numberOfSectors-1, 50, 255);
      std::cout << "creating " << toSend << std::endl;
      outgoingPacketQueue.push_back(toSend);
    }
    nextLinkState = WaitingForGroupInitsToFinish;
    WaitingForGroupInitsToFinish_timer = currentTime + WaitingForGroupInitsToFinish_timeout;
  }
    
  if (currentLinkState == WaitingForGroupInitsToFinish) {
    if (hardwareIsSending) { /*FIXME - should put this in a BaseStationLayers base class*/
      WaitingForGroupInitsToFinish_timer++;
    }
    if (currentTime > WaitingForGroupInitsToFinish_timer) {
      nextLinkState = Initialised;
    }
  }
    
  if (currentLinkState == Initialised) {
      linkLayerInitialised = true;
  }
  
  DiscreteSim::linkLayerLogic ();
  /* TODO packet handler section */
}



void Link::proxied_wrapUpPhase () {
  //std::cout << "in SensorLayers::Link::proxied_wrapUpPhase ()" << std::endl;
  currentLinkState = nextLinkState;
}

} /* end of namespace BaseStationLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */




