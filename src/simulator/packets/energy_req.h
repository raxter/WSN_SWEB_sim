#ifndef __WSN_SIMULATOR_PACKET_ENERGY_REQ_H__
#define __WSN_SIMULATOR_PACKET_ENERGY_REQ_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

class EnergyReq : public BasePacket {

  public:

    EnergyReq (int sendStrength, const Node::BaseNode& node, int dstGrpId);
    ~EnergyReq ();
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
