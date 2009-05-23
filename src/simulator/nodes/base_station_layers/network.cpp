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

}

Network::~Network(){

}


void Network::proxied_setUpPhase () {
  //std::cout << "in BaseStationLayers::Network::proxied_setUpPhase ()" << std::endl;
  nextNetworkState = currentNetworkState;
}


void Network::networkLayerLogic (){
  std::cout << "in BaseStationLayers::Network::networkLayerLogic ()" << std::endl;
  if (linkLayerInitialised) {
    if (currentNetworkState == WaitingForReply) {
      if (receivedPacket && receivedPacket->type == PacketTypes::DataSend)
        nextNetworkState = Running;
    }
    if (currentNetworkState == NetworkUninitialised)
      nextNetworkState = Running;
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




















