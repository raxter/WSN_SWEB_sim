#include "grp_init.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

GrpInit::GrpInit (int signalStrength, const Node::BaseNode& node, int dstGrpId) : 
        BasePacket (signalStrength, PacketTypes::GrpInit, node, -1, dstGrpId) {
        
  size = 100; /*TODO calculate*/

}


GrpInit::~GrpInit () {

}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


