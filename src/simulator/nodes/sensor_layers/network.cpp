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
  HeadReAlloc_timeout = 600;
  for (int i = 0 ; i < 3 ; i++)
    for (int j = 0 ; j < 3 ; j++)
      routeTable[i][j] = -1;
}

Network::~Network(){}


bool Network::isHead() const {

  return id == routeTable[1][1];
}



void Network::proxied_setUpPhase () {
  //std::cout << "in SensorLayers::Network::proxied_setUpPhase ()" << std::endl;
  nextNetworkState = currentNetworkState;
}


#define DEBUG(x) if (false/*this->id == 64 || this->id == 30*/) {if (this->id == 30) std::cout << "\t\t\t\t\t\t\t\t"; std::cout << "id = " << id << " | " << x << std::endl;}

void Network::networkLayerLogic (){
  //DEBUG("in SensorLayers::Network::networkLayerLogic ()");
  //std::cout << "in SensorLayers::Network::networkLayerLogic ()" << std::endl;
  //std::cout << currentLinkState << ":" << LinkUninitialised << std:: endl;
  bool isHead = this->isHead();
  if (receivedPacket && receivedPacket->type == PacketTypes::HeadReAlloc) {
        
    DEBUG("receivedPacket! from " << receivedPacket->srcId << " type " << receivedPacket->type);
    DEBUG("type HeadReAlloc"); 
    //std::cout << "type EnergyReq" << std::endl;
    
    const Packet::HeadReAlloc * reallocPacket = dynamic_cast<const Packet::HeadReAlloc*>(receivedPacket);
    
    #define GET_ID_OF(row,col) (grpId + (numberOfSectors*((row)-1)) - ((col)-1))
    
    DEBUG("HeadReAlloc from group " << reallocPacket->srcGrpId << " realloc to node " << reallocPacket->newHeadId << " | this->grpId = " << grpId); 
    for (int r = 0 ; r < 3 ; r++) {
      for (int c = 0 ; c < 3 ; c++) {
        if (reallocPacket->srcGrpId == GET_ID_OF(r,c)) {
          
          //if (r == 1 && c == 1 && !isHead && id == reallocPacket->newHeadId)
          //  thisNodeIsNewHead = true;
          
          DEBUG("setting routeTable[" << r << "][" << c << "] = " << reallocPacket->newHeadId); 
          routeTable[r][c] = reallocPacket->newHeadId;
        }
      }
    }
    
      
    #undef GET_ID_OF
    
    if (currentNetworkState == InitialisingGroup && reallocPacket->srcGrpId == grpId)
      nextNetworkState = Running;
  
  }
  if (currentNetworkState == NetworkUninitialised && currentLinkState == Initialised) {
    //std::cout << "initialising Network layer" << std:: endl;
    
    double b = threshDegree*threshId;
    double c = threshDegree*(threshId+1);
    double A = 2*M_PI/maxNumberOfSectors;
    double a = sqrt(b*b+c*c-2*b*c*cos(A));
    
    outgoingPacketQueue.push_back(new Packet::GrpInit(a, *this, grpId));
    
    nextNetworkState = InitialisingGroup;
    DEBUG("networkState -> InitialisingGroup");
    InitialisingGroup_timer = currentTime + InitialisingGroup_timeout;
  }
  if (currentNetworkState == InitialisingGroup) {
    if (hardwareIsSending || !inTimeSlot() ) {
      InitialisingGroup_timer++;
    }
    //if (id == 1)
    //  std::cout << "currentTime = " << currentTime << " > "<< InitialisingGroup_timer << " = InitialisingGroup_timer" << std::endl;
    if (currentTime > InitialisingGroup_timer) {
      
      
      int minId = id;
      for (int i = 0 ; i < groupNodeIds.size() ; i++) {
        if (groupNodeIds[i] < minId)
          minId = groupNodeIds[i];
      }
      routeTable[1][1] = minId;
      
      DEBUG("this (" << id << ") of group " << grpId << " chose " << routeTable[1][1] << " as head initially"); 
      //std::cout << "this (" << id << ") of group " << grpId << " chose " << routeTable[1][1] << " as head" << std::endl;
      nextNetworkState = (routeTable[1][1] == id?HeadReAlloc:Running);
      if (nextNetworkState == HeadReAlloc) {DEBUG("networkState -> HeadReAlloc");}
      else {DEBUG("networkState -> Running");}
    }
  }
  if (currentNetworkState != NetworkUninitialised && nextNetworkState != NetworkUninitialised) {
    if (receivedPacket) {
      DEBUG("receivedPacket! from " << receivedPacket->srcId << " type " << receivedPacket->type);
      //std::cout << "receivedPacket!" << std::endl;
      if (receivedPacket->type == PacketTypes::GrpInit) {
        DEBUG("type GrpInit"); 
        //std::cout << "type GrpInit" << std::endl;
        groupNodeIds.push_back(receivedPacket->srcId);
      
      }
      if (receivedPacket->type == PacketTypes::EnergyReq) {
        DEBUG("type EnergyReq"); 
        //std::cout << "type EnergyReq" << std::endl;
        outgoingPacketQueue.push_back(new Packet::EnergySend(dist(receivedPacket->srcId, id), *this, receivedPacket->srcId, energyRemaining));
      
      }
      
      if (receivedPacket->type == PacketTypes::DataReq) {
      
        DEBUG("type DataReq"); 
        int nextHopId = getNextHop();
        
        outgoingPacketQueue.push_back(new Packet::DataSend(dist(nextHopId, id), *this, nextHopId, id));
      }
      if (receivedPacket->type == PacketTypes::DataSend) {
      
        int nextHopId = getNextHop();
        
        const Packet::DataSend * dataSendPacket = dynamic_cast<const Packet::DataSend*>(receivedPacket);
        outgoingPacketQueue.push_back(new Packet::DataSend(dist(nextHopId, id), *this, nextHopId, dataSendPacket->origSrcId));
      }
    }
    
  }
  if (currentNetworkState == HeadReAlloc) {

      int maxDist = 0;
      for (int i = 0 ; i < groupNodeIds.size() ; i++) {
        int signalDist = dist(id, groupNodeIds[i]);
        if (maxDist < signalDist)
          maxDist = signalDist;
      }
      DEBUG("sending energy req");
      BasePacket* toSend = new Packet::EnergyReq(maxDist, *this, grpId);
      //std::cout << "creating " << toSend << std::endl;
      outgoingPacketQueue.push_back(toSend);
      nextNetworkState = HeadReAllocWait;
      DEBUG("networkState -> HeadReAllocWait");
  }
  if (currentNetworkState == HeadReAllocWait) {
    if (receivedPacket && receivedPacket->type == PacketTypes::EnergySend) {
      DEBUG("type EnergySend"); 
      const Packet::EnergySend * packet = dynamic_cast<const Packet::EnergySend*>(receivedPacket); 
      groupEnergies.push(std::make_pair(packet->energyRemaining, packet->srcId));
    }
    
    if (groupEnergies.size () == groupNodeIds.size()) { // then we have all the energies 
      // reallocating head
      int newHead;
      DEBUG("have all energy levels!")
      groupEnergies.push(std::make_pair(energyRemaining, id));
      //if(!groupEnergies.empty())
      { 
      
        double b = threshDegree*(threshId-1);
        double c = threshDegree*(threshId+2);
        double A = 2*M_PI/maxNumberOfSectors;
        double a = sqrt(b*b+c*c-2*b*c*cos(A));
      
        newHead = groupEnergies.top().second;
        
        
        DEBUG("sending realloc - setting to " << newHead);
        //if (newHead != id)
          outgoingPacketQueue.push_back(new Packet::HeadReAlloc(a, *this, grpId, newHead));
        
      }
      while(!groupEnergies.empty()) groupEnergies.pop();
      
      
      HeadReAlloc_timer = currentTime + HeadReAlloc_timeout;
        
      DEBUG("Headnode transfer " << routeTable[1][1] << " -> " << newHead);
      routeTable[1][1] = newHead;
      
      nextNetworkState = Running;
      DEBUG("networkState -> Running");
      
      //if (isHead)
      //  thisNodeIsNewHead = true;
    }
  }
  if (currentNetworkState == Running) {
    
    //DEBUG("routeTable[1][1] = " << routeTable[1][1]);
    if (isHead) {
      //DEBUG(currentTime << " > " << HeadReAlloc_timer);
      if (!inTimeSlot()) {
        HeadReAlloc_timer++;
      }
      if (currentTime > HeadReAlloc_timer) {
        
        nextNetworkState = HeadReAlloc;
      }
    }
  }
  
  if (this->isHead() && !isHead) { // then it is just become head
    // set timer for head realloc
    
    DEBUG("became HeadNode");
    HeadReAlloc_timer = currentTime + HeadReAlloc_timeout;
  }
  
  /*if (id == 95) {
    std::cout << id << std::endl;

    for (int i = 0 ; i < 3 ; i++)
      std::cout << routeTable[i][0] << " \t " << routeTable[i][1] << " \t " << routeTable[i][2] << std::endl;
  }*/
}


void Network::proxied_wrapUpPhase () {
  //std::cout << "in SensorLayers::Network::proxied_wrapUpPhase ()" << std::endl;
  currentNetworkState = nextNetworkState;
}





} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */













