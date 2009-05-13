#include "node.h"

namespace WSN
{
namespace Simulator
{

using namespace std;


Node::Node(int xIn, int yIn)
{
    state = IDLE;
    init();
    x= xIn;
    y=yIn;
    cluster=-1;
}

void Node::init()
{
  energyRemaining=100;///out of a 100 - needs to be changed to a constant MAX_NODE_ENGERGY
  
}

bool Node::isHead()
{
        return routeTable[1][1];
}

void Node::setHead(bool trueForIsTheHead)
{
    routeTable [1][1] = trueForIsTheHead;
}

void Node::setCluster(int cluIn)
{
    cluster = cluIn;
}


int Node::getCluster()
{
    return cluster;
}

Node::~Node()
{
}

Node Node::getNextHop()
{
    return Node();
}

void Node::setRT(int c22,int c21,int c20, int c12,  int c10, int c02, int c01, int c00)
{
    //int hello [3];
    //hello = {4,3,2};

    /*FIXME why??????????*/
    //routeTable  = {{c00,c01,c02},{c10,0,c12},{c20,c21,c22}};

    routeTable[2][2] = c22;
    routeTable[2][1] = c21;
    routeTable[2][0] = c20;

    routeTable[1][2] = c12;
    ///center "isHead" node at [1][1]
    routeTable[1][0] = c10;

    routeTable[0][2] = c02;
    routeTable[0][1] = c01;
    routeTable[0][0] = c00;
}

void Node::printTable()
{
  cout <<routeTable[0][0]<<"  "<<routeTable[0][1]<<"  "<<routeTable[0][2]<<endl;
  cout <<routeTable[1][0]<<"  "<<getCluster()<<"  "<<routeTable[1][2]<<endl;
  cout <<routeTable[2][0]<<"  "<<routeTable[2][1]<<"  "<<routeTable[2][2]<<endl;
}

int * Node::getRT(int row)
{
    /*FIXME why cant an int ** return routeTable FFFFFFFFFUUUUUUUUUUUU????*/
    //return routeTable
    return routeTable[row];
}


} /* end of namespace Simulator */

} /* end of namespace WSN */


