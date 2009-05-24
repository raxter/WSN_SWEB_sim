#ifndef __WSN_SIMULATOR_PACKET_HEAD_REALLOC_H__
#define __WSN_SIMULATOR_PACKET_HEAD_REALLOC_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

class HeadReAlloc : public BasePacket {

  public:

    HeadReAlloc (int sendStrength, const Node::BaseNode& node, int srcGrpId, int newHeadId);
    ~HeadReAlloc ();
    
    
    const int srcGrpId;
    const int newHeadId;
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
