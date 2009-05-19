#ifndef __WSN_SIMULATOR_PACKET_H__
#define __WSN_SIMULATOR_PACKET_H__

#include "node.h"

namespace WSN
{

namespace Simulator
{

class Packet    {

  public:

    Packet ();
    ~Packet ();


    Node * source;
    Node * dest;
    double data;
    int size; // in bytes
};

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif // __WSN_SIMULATOR_PACKET_H__
