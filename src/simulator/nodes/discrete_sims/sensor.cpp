



#include "sensor.h"
#include <iostream>
#include <typeinfo>

namespace WSN
{

namespace Simulator
{

namespace Nodes
{

namespace DiscreteSims
{


using namespace std;

/****************************************************************************
**
** Author: Julian Hulme
** Author: Richard Baxter
**
****************************************************************************/


Sensor::Sensor(int id, double x, double y) : DiscreteSim(id, x, y, Node::Idle), _cluster(-1)
{
  energyRemaining=100;
  for (int i = 0 ; i < 3 ; i++)
    for (int j = 0 ; j < 3 ; j++)
      routeTable [i][j] = 0;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

Sensor::~Sensor()
{
}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

bool Sensor::isHead() const
{
  return routeTable[1][1] == this;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim * Sensor::getHead() const // get head... lol
{
  return routeTable[1][1];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Sensor::setHead(DiscreteSim * nodeId)
{
    routeTable [1][1] = nodeId;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

int Sensor::cluster() const {
  return _cluster;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void Sensor::setCluster(int cluster)
{
  _cluster = cluster;
}

/****************************************************************************
**
** Author: Julian Hulme
**
** Returns id of next hop
**
****************************************************************************/

Node * Sensor::getNextHop()  const
{
  std::cout << isHead() << std::endl;
  printTable();
  if (isHead()) ///route to next cluster head
  {
    ///Get the next nearest head node: contenders are [0][0], [0][1] and [0][2] if they exist

    DiscreteSim * nextSensor;


    if (routeTable[0][1] != NULL)
      nextSensor = routeTable[0][1];
    else if (routeTable[0][0] != NULL)
      nextSensor = routeTable[0][0];
    else if (routeTable[0][2] != NULL)
      nextSensor = routeTable[0][2];
    //else nextSensor = & ///this is the current SWEB problem where to go if node is isolated
    return nextSensor;


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

void Sensor::setRouteTable ( DiscreteSim * c22, DiscreteSim * c21,DiscreteSim * c20,DiscreteSim * c12,DiscreteSim * c10, DiscreteSim * c02,DiscreteSim * c01,DiscreteSim * c00)
{
  routeTable[2][ 2] = c22;
  routeTable[2][ 1] = c21;
  routeTable[2][ 0] = c20;
  routeTable[1][ 2] = c12;
  ///center "isHead" node at [1][1]
  routeTable[1][ 0] = c10;
  routeTable[0][ 2] = c02;
  routeTable[0][ 1] = c01;
//  cout << "here: "<<routeTable[0][1]->cluster<<endl;
  routeTable[0][ 0] = c00;

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

DiscreteSim * Sensor::getRouteTable(int row, int column) const
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

void Sensor::printTable() const
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
      if (routeTable[a][b] != NULL) {
        if (typeid(routeTable[a][b]) == typeid(Sensor*))
          cout << ((Sensor*)routeTable[a][b])->cluster() <<"  ";
        else
          cout << "X";
      }
      else 
        cout << "N  ";
    }
    cout<<endl;
  }

  //cout<<routeTable[0][1]->getCluster();
  //cout<<"  "<<routeTable[0][2]->getCluster()<<endl;
  //cout <<routeTable[1][0]->getCluster()<<"  "<<getCluster()<<"  "<<routeTable[1][2]->getCluster()<<endl;
  //cout <<routeTable[2][0]->getCluster()<<"  "<<routeTable[2][1]->getCluster()<<"  "<<routeTable[2][2]->getCluster()<<endl;

}

} /* end of namespace DiscreteSims */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


