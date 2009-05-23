#include "data_req.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Packet
{

DataReq::DataReq (int signalStrength, const Node::BaseNode& node, int dstId) : 
        BasePacket (signalStrength, PacketTypes::DataReq, node, dstId, -1) {
        
  size = 40; /*TODO calculate*/

}


DataReq::~DataReq () {

}

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


