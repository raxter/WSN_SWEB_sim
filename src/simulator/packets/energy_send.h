#ifndef __WSN_SIMULATOR_PACKET_ENERGY_SEND_H__
#define __WSN_SIMULATOR_PACKET_ENERGY_SEND_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

class EnergySend : public BasePacket {

  public:

    EnergySend (int sendStrength, const Node::BaseNode& node, int dstId, long long energyRemaining);
    ~EnergySend ();
    
    
    const long long energyRemaining;
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
