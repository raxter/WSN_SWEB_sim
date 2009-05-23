

#include "base_packet.h"


namespace WSN
{

namespace Simulator
{

BasePacket::BasePacket (int signalStrength, PacketTypes::Type type, const Node::BaseNode& node, int dstId, int dstGrpId) : signalStrength(signalStrength), type(type), srcId(node.id), dstId(dstId), dstGrpId(dstGrpId) {
  size = 0;
}


BasePacket::~BasePacket () {

}


int BasePacket::getSizeInBytes() const {

  return size;

}


} /* end of namespace Simulator */


} /* end of namespace WSN */


