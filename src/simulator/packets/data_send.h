#ifndef __WSN_SIMULATOR_PACKET_DATA_SEND_H__
#define __WSN_SIMULATOR_PACKET_DATA_SEND_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

class DataSend : public BasePacket {

  public:

    DataSend (int sendStrength, const Node::BaseNode& node, int dstId, int origSrcId);
    ~DataSend ();
    
  
    const int origSrcId;
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
