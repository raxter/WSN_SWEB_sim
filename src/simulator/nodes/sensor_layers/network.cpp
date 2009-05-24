#include "network.h"

#include <cmath>
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

  InitialisingGroup_timeout = 40;
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
<<<<<<< HEAD:src/simulator/nodes/sensor_layers/network.cpp

=======
  
>>>>>>> 4d6c8db6ca3489d8dc0ca06751de06dba5d5b5ec:src/simulator/nodes/sensor_layers/network.cpp
  //std::cout << currentLinkState << ":" << LinkUninitialised << std:: endl;
  if (currentNetworkState == NetworkUninitialised && currentLinkState == Initialised) {
    //std::cout << "initialising Network layer" << std:: endl;
    
    double b = threshDegree*threshId;
    double c = threshDegree*(threshId+1);
    double A = 2*M_PI/maxNumberOfSectors;
    double a = sqrt(b*b+c*c-2*b*c*cos(A));
    
    outgoingPacketQueue.push_back(new Packet::GrpInit(a, *this, grpId));
    
    nextNetworkState = InitialisingGroup;
    InitialisingGroup_timer = currentTime + InitialisingGroup_timeout;
  }
  if (currentNetworkState == InitialisingGroup) {
    if (hardwareIsSending || !inTimeSlot() ) {
      InitialisingGroup_timer++;
    }
    //if (id == 1)
    //  std::cout << "currentTime = " << currentTime << " > "<< InitialisingGroup_timer << " = InitialisingGroup_timer" << std::endl;
    if (currentTime > InitialisingGroup_timer) {
<<<<<<< HEAD:src/simulator/nodes/sensor_layers/network.cpp

=======
      
      std::cout << "this (" << id << ") of group " << grpId << " chose " << routeTable[1][1] << " as head" << std::endl;
>>>>>>> 4d6c8db6ca3489d8dc0ca06751de06dba5d5b5ec:src/simulator/nodes/sensor_layers/network.cpp
      int minId = id;
      for (int i = 0 ; i < groupNodeIds.size() ; i++) {
        if (groupNodeIds[i] < minId)
          minId = groupNodeIds[i];
      }
      routeTable[1][1] = minId;
      std::cout << "this (" << id << ") of group " << grpId << " chose " << routeTable[1][1] << " as head" << std::endl;
      nextNetworkState = (routeTable[1][1] == id?HeadReAlloc:Running);
    }
  }
  if (currentNetworkState != NetworkUninitialised && nextNetworkState != NetworkUninitialised) {
<<<<<<< HEAD:src/simulator/nodes/sensor_layers/network.cpp



=======
    
    if (receivedPacket) {
      std::cout << "receivedPacket!" << std::endl;
      if (receivedPacket->type == PacketTypes::GrpInit) {
        std::cout << "type GrpInit" << std::endl;
        groupNodeIds.push_back(receivedPacket->srcId);
      
      }
      if (receivedPacket->type == PacketTypes::EnergyReq) {
        std::cout << "type EnergyReq" << std::endl;
          //outgoingPacketQueue.push_back(new Packet::EnergySend(dist(receivedPacket->scrId, id), *this, receivedPacket->scrId));
      
      }
    }
>>>>>>> 4d6c8db6ca3489d8dc0ca06751de06dba5d5b5ec:src/simulator/nodes/sensor_layers/network.cpp
  }
  if (currentNetworkState == HeadReAlloc) {

      int maxDist = 0;
      for (int i = 0 ; i < groupNodeIds.size() ; i++) {
        int signalDist = dist(id, groupNodeIds[i]);
        if (maxDist < signalDist)
          maxDist = signalDist;
      }
      BasePacket* toSend = new Packet::EnergyReq(maxDist, *this, grpId);
<<<<<<< HEAD:src/simulator/nodes/sensor_layers/network.cpp
      //std::cout << "creating " << toSend << std::endl;
=======
>>>>>>> 4d6c8db6ca3489d8dc0ca06751de06dba5d5b5ec:src/simulator/nodes/sensor_layers/network.cpp
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













