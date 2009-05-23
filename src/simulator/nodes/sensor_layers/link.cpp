#include "link.h"



#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace SensorLayers
{


Link::Link(){
}


Link::~Link() {

}


void Link::proxied_setUpPhase () {
  //std::cout << "in SensorLayers::Link::proxied_setUpPhase ()" << std::endl;

  nextLinkState = currentLinkState;
}


void Link::linkLayerLogic (){
  //std::cout << "in SensorLayers::Link::linkLayerLogic ()" << std::endl;
  
  if (currentLinkState == LinkUninitialised) {
    //std::cout << "receivedPacket = " << receivedPacket << std::endl;
    if (receivedPacket && receivedPacket->type == PacketTypes::Init) {
      
      const Packet::Init * packet = dynamic_cast<const Packet::Init*>(receivedPacket); 
      
      //std::cout << "Init::Init| dstSectorId = " << packet->dstSectorId << "| maxSector = " << packet->maxSector << "| threshValue = " << packet->threshValue << "| sendStrength = " << packet->sendStrength << "| maxId = " << packet->maxId << std::endl;
      
      maxNumberOfIds = packet->maxId;
      sectorId = packet->dstSectorId;


      /* TODO Jules do these methods */
      //distToBase = 
      maxNumberOfSectors = packet->maxSector;
      threshId = calcThresh(packet->threshValue, receivedPacketDistance);
      grpId = calcGroupId(threshId, sectorId, maxNumberOfSectors);
      maxNumberOfGroups = calcMaxNumberOfGroup(packet->threshValue, packet->sendStrength, maxNumberOfSectors);
      
      nextLinkState = Initialised;
    }
  
  }
  
  
}


void Link::proxied_wrapUpPhase () {
  //std::cout << "in SensorLayers::Network::proxied_wrapUpPhase ()" << std::endl;
  currentLinkState = nextLinkState;
}










} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */








