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
Node::Node()
{
  //cluster = 0;
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
  //cluster = 0 ;
//  nul(0,0,0);

}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

bool Node::isHead() const
{
  return routeTable[1][1] == this;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

Node * Node::getHead() // get head... lol
{
  return routeTable[1][1];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::setHead(Node * nodeId)
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

Node * Node::getNextHop()
{

  if (isHead()) ///route to next cluster head
  {
    ///Get the next nearest head node: contenders are [0][0], [0][1] and [0][2] if they exist

    Node * nextNode;


    if (getRouteTable(0,1) != NULL)
      nextNode = getRouteTable(0,1);
    else if (getRouteTable(0,0) != NULL)
      nextNode = getRouteTable(0,0);
    else if (getRouteTable(0,2) != NULL)
      nextNode = getRouteTable(0,2);
    //else nextNode = & ///this is the current SWEB problem where to go if node is isolated
    return nextNode;


  }
  else ///route to head node of cluster
  {
      return getHead();
  }

}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::setRouteTable ( Node * c22, Node * c21,Node * c20,Node * c12,Node * c10, Node * c02,Node * c01,Node * c00)
{
  assignToRouteTable(2, 2, c22);
  assignToRouteTable(2, 1, c21);
  assignToRouteTable(2, 0, c20);
  assignToRouteTable(1, 2, c12);
  ///center "isHead" node at [1][1]
  assignToRouteTable(1, 0, c10);
  assignToRouteTable(0, 2, c02);
  assignToRouteTable(0, 1, c01);
//  cout << "here: "<<routeTable[0][1]->cluster<<endl;
  assignToRouteTable(0, 0, c00);

}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
void Node::assignToRouteTable(int row, int col, Node * in)
{
  //if (in = NULL)
  //  routeTable[row][col]=*nul;
  //else
    routeTable[row][col] = in;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

Node * Node::getRouteTable(int row, int column)
{
    /*FIXME why cant an int ** return routeTable FFFFFFFFFUUUUUUUUUUUU????*/
    //return routeTable
    return routeTable[row][column];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Node::printTable()
{
  /* FIXME i removed this because it was generating too much spew */
  for (int a= 0 ; a<3 ; a++)
  {
    for (int b = 0 ; b < 3 ; b++)
    {
      if ((b==1)&&(a==1))
      {
        cout << "   ";
        b=2;
      }
      if (routeTable[a][b] != NULL)
        cout <<routeTable[a][b]->getCluster()<<"  ";
      else cout << "N  ";
    }
    cout<<endl;
  }

  //cout<<routeTable[0][1]->getCluster();
  //cout<<"  "<<routeTable[0][2]->getCluster()<<endl;
  //cout <<routeTable[1][0]->getCluster()<<"  "<<getCluster()<<"  "<<routeTable[1][2]->getCluster()<<endl;
  //cout <<routeTable[2][0]->getCluster()<<"  "<<routeTable[2][1]->getCluster()<<"  "<<routeTable[2][2]->getCluster()<<endl;

}


} /* end of namespace Simulator */

} /* end of namespace WSN */


