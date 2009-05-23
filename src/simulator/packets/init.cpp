#include "init.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

Init::Init (int signalStrength, const Node::BaseNode& node, int dstSectorId, int maxSector, int threshValue, int maxId) : 
        BasePacket (signalStrength, PacketTypes::Init, node, -1, -1), 
        dstSectorId(dstSectorId), 
        maxSector(maxSector),
        threshValue(threshValue), 
        sendStrength(signalStrength), 
        maxId(maxId)   {
        
  size = 100; /*TODO calculate*/
  
  std::cout << "Init::Init| dstSectorId = " << dstSectorId << "| maxSector = " << maxSector << "| threshValue = " << threshValue << "| sendStrength = " << sendStrength << "| maxId = " << maxId << std::endl;

}


Init::~Init () {



}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


