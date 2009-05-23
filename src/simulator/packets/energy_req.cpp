#include "energy_req.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

EnergyReq::EnergyReq (int signalStrength, const Node::BaseNode& node, int dstGrpId) : 
        BasePacket (signalStrength, PacketTypes::EnergyReq, node, -1, dstGrpId) {
        
  size = 40; /*TODO calculate*/

}


EnergyReq::~EnergyReq () {

}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


