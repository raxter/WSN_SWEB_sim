#ifndef __WSN_SIMULATOR_BASE_PACKET_H__
#define __WSN_SIMULATOR_BASE_PACKET_H__

#include "nodes/base_node.h"

namespace WSN
{

namespace Simulator
{


namespace PacketTypes
{
  enum Type {NoType, Init, GrpInit, EnergyReq, EnergySend, DataReq, DataSend, HeadReAlloc};
}

/* TODO make const */
class BasePacket  {

  public:


  protected:
    BasePacket (int signalStrength, PacketTypes::Type type, const Node::BaseNode& node, int dstId = -1, int dstGrpId = -1);
    virtual ~BasePacket ();

  public:
    const int signalStrength;

    /* packet data */
    const int srcId;
    const int dstId;
    const int dstGrpId;
    const PacketTypes::Type type;
    int getSizeInBytes() const;
  protected:
    int size; // in bytes
};

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
