#ifndef __WSN_SIMULATOR_NODE_H__
#define __WSN_SIMULATOR_NODE_H__

#include "constants.h"

namespace WSN
{

namespace Simulator
{

class Node  {

    public:
    ///Constructors/Destructors
    Node();
    Node(int x, int y);
    ~Node();

    ///mem allocation


    ///attributes
    int x,y; /* FIXME - doubles rather, perhaps (?) - raxter */
    bool head;
    int cluster;
    int energyRemaining;

    ///functions
    bool isHead();
    void setHead(bool trueForIsTheHead);
    void init();
    Node getNextHop();


};

} /* end of namespace Simulator */


} /* end of WSN namespace */

#endif
