#include "data_send.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

DataSend::DataSend (int signalStrength, const Node::BaseNode& node, int dstId, int origSrcId, int energyUsed, int hops) : 
        BasePacket (signalStrength, PacketTypes::DataSend, node, dstId, -1), origSrcId(origSrcId), energyUsed(energyUsed), hops(hops) {
        
  size = 2048; /*TODO calculate*/

}


DataSend::~DataSend () {

}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


