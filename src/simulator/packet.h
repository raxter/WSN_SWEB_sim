#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

#include "node.h"

class Packet    {

      Packet ();
      ~Packet ();


      Node * source;
      Node * dest;
      double data;
    };
#endif // PACKET_H_INCLUDED
