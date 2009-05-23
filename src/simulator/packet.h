#ifndef __WSN_SIMULATOR_PACKET_H__
#define __WSN_SIMULATOR_PACKET_H__

#include "nodes/base_node.h"

namespace WSN
{

namespace Simulator
{

/* TODO make const */
class Packet    {

  public:

    Packet ();
    ~Packet ();


    const int srcId;
    const int dstId;
    
    int size; // in bytes
};

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
