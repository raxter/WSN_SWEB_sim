#include "head_realloc.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

HeadReAlloc::HeadReAlloc (int signalStrength, const Node::BaseNode& node, int srcGrpId, int newHeadId) : 
        BasePacket (signalStrength, PacketTypes::HeadReAlloc, node, -1, -1), srcGrpId(srcGrpId), newHeadId(newHeadId) {
        
  size = 100; /*TODO calculate*/

}


HeadReAlloc::~HeadReAlloc () {

}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


