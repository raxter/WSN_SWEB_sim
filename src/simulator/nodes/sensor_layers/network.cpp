#include "network.h"


#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace SensorLayers
{


Network::Network() {

  InitialisingGroup_timeout = 30;
  for (int i = 0 ; i < 3 ; i++)
    for (int j = 0 ; j < 3 ; j++)
      routeTable[i][j] = -1;
}

Network::~Network(){}


bool Network::isHead() const {

  return this->id == routeTable[1][1];
}



void Network::proxied_setUpPhase () {
  //std::cout << "in SensorLayers::Network::proxied_setUpPhase ()" << std::endl;
  nextNetworkState = currentNetworkState;
}


void Network::networkLayerLogic (){
  //std::cout << "in SensorLayers::Network::networkLayerLogic ()" << std::endl;
  
  std::cout << currentLinkState << ":" << LinkUninitialised << std:: endl;
  if (currentNetworkState == NetworkUninitialised && currentLinkState == Initialised) {
    std::cout << "initialising Network layer" << std:: endl;
    nextNetworkState = InitialisingGroup;
    InitialisingGroup_timer = currentTime + InitialisingGroup_timeout;
  }
  if (currentNetworkState == InitialisingGroup && routeTable[1][1] != id) {
    if (hardwareIsSending) { /*FIXME - should put this in a BaseStationLayers base class*/
      InitialisingGroup_timer++;
    }
    if (currentTime > InitialisingGroup_timer) {
      
      int minId = id;
      for (int i = 0 ; i < groupNodeIds.size() ; i++) {
        if (groupNodeIds[i] < minId)
          minId = groupNodeIds[i];
      }
      routeTable[1][1] = minId;
      nextNetworkState = (routeTable[1][1] == id?HeadReAlloc:Running);
    }
  }
  if (currentNetworkState != NetworkUninitialised && nextNetworkState != NetworkUninitialised) {
    
    
    
  }
  if (currentNetworkState == HeadReAlloc) {
    
      int maxDist = 0;
      for (int i = 0 ; i < groupNodeIds.size() ; i++) {
        int signalDist = dist(id, groupNodeIds[i]);
        if (maxDist < signalDist)
          maxDist = signalDist;
      }
      BasePacket* toSend = new Packet::EnergyReq(maxDist, *this, grpId);
      std::cout << "creating " << toSend << std::endl;
      outgoingPacketQueue.push_back(toSend);
  
  }
  if (currentNetworkState == HeadReAllocWait) {
  
  
  }
}


void Network::proxied_wrapUpPhase () {
  //std::cout << "in SensorLayers::Network::proxied_wrapUpPhase ()" << std::endl;
  currentNetworkState = nextNetworkState;
}





} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */













