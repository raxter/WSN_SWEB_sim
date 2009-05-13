#ifndef __WSN_SIMULATOR_NODE_H__
#define __WSN_SIMULATOR_NODE_H__

#include "constants.h"


#include <iostream>


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
    enum State {IDLE, SENDING, RECEIVING, READY_TO_SEND, OUT_OF_ENERGY};

    int x,y; /* FIXME - doubles rather, perhaps (?) - raxter */
    int cluster;
    int routeTable [3][3];
    int energyRemaining;

    ///functions
    bool isHead();
    void setHead(bool trueForIsTheHead);
    void init();
    Node getNextHop();
    void setCluster(int cluIn);
    int getCluster();
    void setRT(int  c22,int  c21,int  c20,int  c12, int  c10, int  c02, int  c01, int  c00);
    void printTable();
    int * getRT(int row);
};


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
