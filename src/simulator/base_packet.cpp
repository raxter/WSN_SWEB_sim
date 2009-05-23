

#include "base_packet.h"


namespace WSN
{

namespace Simulator
{

BasePacket::BasePacket (int signalDistance, PacketTypes::Type type, const Node::BaseNode& node, int dstId, int dstGrpId) : signalDistance(signalDistance), type(type), srcId(node.id), dstId(dstId), dstGrpId(dstGrpId) {
  size = 0;
}


BasePacket::~BasePacket () {

}


int BasePacket::getSizeInBytes() const {

  return size;

}


} /* end of namespace Simulator */


} /* end of namespace WSN */


