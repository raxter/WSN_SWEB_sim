#ifndef __WSN_SIMULATOR_PACKET_GRP_INIT_H__
#define __WSN_SIMULATOR_PACKET_GRP_INIT_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

class GrpInit : public BasePacket {

  public:

    GrpInit (int sendStrength, const Node::BaseNode& node, int dstGrpId);
    ~GrpInit ();
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
