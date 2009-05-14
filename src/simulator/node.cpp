#include "node.h"

namespace WSN
{
namespace Simulator
{

using namespace std;

/****************************************************************************
**
** Author: Julian Hulme
** Author: Richard Baxter
**
****************************************************************************/


Node::Node(int id, int x, int y) : id (id), x(x), y(y), cluster(-1), state(IDLE), otherNode(NULL)
{
    init();
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

Node::~Node()
{
}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::init()
{
  energyRemaining=100;///out of a 100 - needs to be changed to a constant MAX_NODE_ENGERGY
  
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

bool Node::isHead() const
{
  return routeTable[1][1] == id;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

int Node::getHead() // get head... lol
{
  return routeTable[1][1];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::setHead(int nodeId)
{
    routeTable [1][1] = nodeId;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::setCluster(int cluster)
{
  this->cluster = cluster;
}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int Node::getCluster()
{
    return cluster;
}
/****************************************************************************
**
** Author: Julian Hulme
**
** Returns id of next hop
**
****************************************************************************/

int Node::getNextHop()
{
  
  /*FIXME routing algorithms should go here since in real life this is where it would be calculated*/
  return id+1;//getHead(); /*FIXME must implement, this method should definitly not go to sensor network*/
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::setRT(int c22, int c21,int c20, int c12,  int c10, int c02, int c01, int c00)
{

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

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int * Node::getRT(int row)
{
    /*FIXME why cant an int ** return routeTable FFFFFFFFFUUUUUUUUUUUU????*/
    //return routeTable
    return routeTable[row];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::printTable()
{
  /* FIXME i removed this because it was generating too much spew */
  //cout <<routeTable[0][0]<<"  "<<routeTable[0][1]<<"  "<<routeTable[0][2]<<endl;
  //cout <<routeTable[1][0]<<"  "<<getCluster()<<"  "<<routeTable[1][2]<<endl;
  //cout <<routeTable[2][0]<<"  "<<routeTable[2][1]<<"  "<<routeTable[2][2]<<endl;
}


} /* end of namespace Simulator */

} /* end of namespace WSN */


