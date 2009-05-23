#ifndef __WSN_SIMULATOR_PACKET_INIT_H__
#define __WSN_SIMULATOR_PACKET_INIT_H__

#include "../base_packet.h"

namespace WSN
{

namespace Simulator
{

namespace Packet
{

/* TODO make const */
class Init : public BasePacket {

  public:

    Init (int sendStrength, const Node::BaseNode& node, int dstSectorId, int maxSector, int threshValue, int maxId);
    ~Init ();
    
  const int dstSectorId;
  const int maxSector;
  const int threshValue;
  const int sendStrength;
  const int maxId;
};

} /* end of namespace Packet */


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
