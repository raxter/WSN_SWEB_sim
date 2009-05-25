#include "network.h"


#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace BaseStationLayers
{


Network::Network(){
  toSendTo = 1;
  networkInitialisation_timeout = 40;
}

Network::~Network(){

}


void Network::proxied_setUpPhase () {
  //std::cout << "in BaseStationLayers::Network::proxied_setUpPhase ()" << std::endl;
  nextNetworkState = currentNetworkState;
}


void Network::networkLayerLogic (){
  //std::cout << "in BaseStationLayers::Network::networkLayerLogic ()" << std::endl;
  if (linkLayerInitialised) {
    if (currentNetworkState == WaitingForReply) {
      if (receivedPacket && receivedPacket->type == PacketTypes::DataSend) {
        const Packet::DataSend * dataSendPacket = dynamic_cast<const Packet::DataSend*>(receivedPacket);
        std::cout << dataSendPacket->hops << "\t" << dataSendPacket->energyUsed << std::endl;
        networkInitialisation_timer = currentTime + networkInitialisation_timeout;
        nextNetworkState = Running;
      }
    }
    if (currentNetworkState == NetworkUninitialised) {
      networkInitialisation_timer = currentTime + networkInitialisation_timeout;
      nextNetworkState = Running;
    }
    if (currentNetworkState == Running) {
    
      //std::cout << "current time slot " << getCurrentTimeSlot() << std::endl;
      if (!inTimeSlot()) {
        networkInitialisation_timer++;
        
        //std::cout << "not in timeslot" << std::endl;
      }
      else {
      
        //std::cout << "in timeslot" << std::endl;
      }
      
      //std::cout << currentTime << " > " << networkInitialisation_timer << std::endl;
      if (currentTime > networkInitialisation_timer) {
      
        Packet::DataReq* dataReq = new Packet::DataReq(500, *this, toSendTo);
        //std::cout << "creating " << toSend << std::endl;
        outgoingPacketQueue.push_back(dataReq);
        
        toSendTo++;
        
        if (toSendTo > maxNumberOfIds)
          toSendTo = 1;
          
          
        nextNetworkState = WaitingForReply;
      }
    }
      
    //if (currentNetworkState == Running && nextNetworkState == Initialised) {
      // FIXME outgoingPackets.push_back(new Packet::DataReq(this, 10/*dstId*/));
    //  nextNetworkState = WaitingForReply;
    //}
  }
  DiscreteSim::networkLayerLogic ();
}

void Network::proxied_wrapUpPhase () {
  //std::cout << "in BaseStationLayers::Network::proxied_wrapUpPhase ()" << std::endl;
  currentNetworkState = nextNetworkState;
}











} /* end of namespace BaseStationLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */




















