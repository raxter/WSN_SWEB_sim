#include "energy_send.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

EnergySend::EnergySend (int signalStrength, const Node::BaseNode& node, int dstId, long long energyRemaining) : 
        BasePacket (signalStrength, PacketTypes::EnergySend, node, dstId, -1), energyRemaining(energyRemaining) {
        
  size = 100; /*TODO calculate*/

}


EnergySend::~EnergySend () {

}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


