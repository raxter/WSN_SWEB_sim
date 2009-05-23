#ifndef __WSN_SIMULATOR_PACKET_DATA_REQ_H__
#define __WSN_SIMULATOR_PACKET_DATA_REQ_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

class DataReq : public BasePacket {

  public:

    DataReq (int sendStrength, const Node::BaseNode& node, int dstId);
    ~DataReq ();
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
