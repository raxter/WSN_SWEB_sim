#include "sensor_network.h"

namespace WSN
{
namespace Simulator
{
using namespace std;


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


SensorNetwork::SensorNetwork(int xRangeIn, int yRangeIn, int noNodesIn, int noSectorsIn) : baseStation(-1)
{
  baseStation.state = Node::READY_TO_SEND;
  noSectors = noSectorsIn;
  scanAngle = 360/noSectors;
  noNodes = noNodesIn;
  createNodes(xRangeIn,yRangeIn);

  init();
  route();

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
SensorNetwork::~SensorNetwork()
{

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

void SensorNetwork::route()
{
  /*RAGE my changes caused this to infinite loop! FIXME - rax*/
  /*Node * curNode = &nodes[97];
  while (curNode != &baseStation)
  {

    curNode = nextHop(curNode);
    ////cout<<"pac from node 97 is in cluster: "<<curNode->getCluster()<<endl;
  }*/

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::determineCluster(Node * in)
{
  int x = in->x;
  int y = in->y;

  double dist = getDistFromBS(in);
  int degreesOutward = (int)dist/(int)threshDegree;

  int relSlice = getSlice(x , y);

  int output = degreesOutward*noSectors + relSlice;

  ///global degreesOutputMax used as a reference later as to how far the web goes
  if (clusterMax < output)
      clusterMax = output;
  ///
  return degreesOutward*noSectors + relSlice;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

Node* SensorNetwork::getNode(int id) {
  return &nodes[id];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::getSlice(int x , int y)
{

  double angle=0 ;
  if  (x*y > 0)
  {
      angle = atan((abs(y)+0.0)/(abs(x)+0.0));
      if (y<0)
          angle = angle + pi;
  }
  else if (x*y < 0)
  {
      angle = atan((y+0.0)/(-x+0.0));
      if (y>0)
          angle = pi - angle;
      else
          angle = 2*pi - angle;
  }
  else if (x==0)
      if (y>0)
          angle = pi/2;
      else if (y < 0)
          angle = 3*pi/2;
      else angle = -1;
  else
  {
      if (x>0)
          angle = 0;
      else if (x < 0)
          angle = -1*pi;
      else angle = -1;
  }
  angle = angle *180/pi;

  int relivantSlice = 0;
  while (angle >= scanAngle)
  {
      relivantSlice++;
      angle -= scanAngle;

  }

  return relivantSlice;

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

/*FIXME if this is the routeing algorithm is should definitly go to the node class, this is a non-centralised routing algo, requires non-centralised routing ;) */
/* should return id maybe? - rax*/
Node * SensorNetwork::nextHop (Node * source)
{
  if (source == &baseStation)
      return source;

  else if (source->isHead()) ///route to next cluster head
  {
    ///Get the next nearest head node: contenders are [0][0], [0][1] and [0][2] if they exist

    int nextClusterNo = source->getRT(0)[1];//ur here




    if (nextClusterNo == -1)
      return &baseStation;
    else 
      return clusterHeads[nextClusterNo];

  }
  else ///route to head node of cluster
  {
      return clusterHeads[source->getCluster()];
  }
}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

std::vector <Node *> SensorNetwork::getNodePointers()
{
  std::vector <Node *> out;
  out.push_back(&baseStation);
  for (int a = 0 ; a < noNodes ; a++)
    out.push_back(&nodes[a]);
  return out;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

std::vector <const Node *> SensorNetwork::getConstNodePointers() const
{
  std::vector <const Node *> out;
  out.push_back(&baseStation);
  for (int a = 0 ; a < noNodes ; a++)
    out.push_back(&nodes[a]);
  return out;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


void SensorNetwork::init() {
  scanAngle = 45;//*PI/180; /*FIXME, should be based on numberOfSectors, doesn't have to be radians though :) */
  threshDegree=25;
  clusterMax=0;

  ///determine all nodes clusters
  for (int a = 0 ; a < noNodes ; a++)
  {
      nodes[a].cluster = determineCluster(&nodes[a]);
      //cout<<"node: "<<a<<" x: "<<nodes[a].x<<" y: "<<nodes[a].y<<" cluster "<<nodes[a].cluster<<endl;

  }

  ///set initial cluster heads
  for (int b = 0 ; b <= clusterMax ; b++)
  {
      vector <Node*> cluster = getCluster(b);
      //cout <<"\nsize: "<< cluster.size()<< endl;

      int lowestRemEnergy = MAX_NODE_ENGERGY+1;
      Node * newHead = NULL;
      for (int c = 0 ; c < cluster.size(); c++)
      {
          //cout << "there are actual nodes in this cluster: "<< " current node in cluster: "<<cluster[c]->cluster<<endl;
          if (cluster[c]->energyRemaining < lowestRemEnergy)
          {
                  lowestRemEnergy = cluster[c]->energyRemaining;
                  newHead = cluster[c];
                  cluster[c]->setHead(true);
          }
      }
      clusterHeads.push_back(newHead);
      //cout<<"cluster "<<b<<" headnode "<<newHead;

  }
  for (int hnC = 0 ; hnC < clusterHeads.size() ; hnC++)
      //cout<<"clust no: "<<hnC<<" CH: "<<getCluster(hnC).size()<<" - "<<clusterHeads[hnC]<<endl;

  ///since head nodes have been determined
  ///create routing tables
  for (int c = 0 ; c < noNodes ; c++)
  {
      double dist = getDistFromBS(&nodes[c]);
      int degreesOutward = (int)dist/(int)threshDegree;



      int relCluster = nodes[c].getCluster();
      ///[2][2]:
      int c22 = (relCluster+1)%noSectors + (degreesOutward+1)*noSectors;
      ///[2][1]:
      int c21 = relCluster+noSectors;
      ///[2][0]:
      int c20 = (relCluster-1)%noSectors + (degreesOutward+1)*noSectors;

      ///[1][2]:
      int c12 = (relCluster +1)%noSectors + degreesOutward*noSectors;
      ///[1][0]:
      int c10 = (relCluster -1)%noSectors + degreesOutward*noSectors;

      ///[0][*]
      int c02,c01,c00 = 0;
      if (relCluster < noSectors)
      {
          ///[0][2]:
          c02 = -1;///-1 = base station
          ///[0][1]:
          c01 = -1;///-1 = base station
          ///[0][0]:
          c00 = -1;///-1 = base station
      }
      else
      {
          ///[0][2]:
          c02 = (relCluster+1)%noSectors + (degreesOutward-1)*noSectors;
            ///[2][1]:
          c01 = relCluster-noSectors;
          ///[2][0]:
          c00 = (relCluster-1)%noSectors + (degreesOutward-1)*noSectors;
      }

      nodes[c].setRT(c22,c21,c20,c12,c10,c02,c01,c00) ;
      //cout<<c<<endl;
      nodes[c].printTable();
      //cout<<endl;

  }

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


vector <Node *> SensorNetwork::getCluster(int clustNo)
{
  vector <Node *> out;
  for (int a = 0 ; a < noNodes ; a++)
  {
          if (nodes[a].cluster == clustNo)
              out.push_back(&nodes[a]);
  }
  return out;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


void SensorNetwork::createNodes(int x , int y)
{
  //cout<<"start of createNodes "<<noNodes<<endl;
  for (int a = 0 ; a < noNodes ; a++)
  {

      int randx = x/2 - rand()%(x+1);
      int randy = y/2 - rand()%(y+1);
      nodes.push_back( Node(a, randx, randy));

  }
  //cout<<"end of createNodes "<<noNodes<<endl;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


double SensorNetwork::dist(int x1, int y1, int x2, int y2)
{

  return sqrt(pow(x2-x1,2) + pow(y2-y1,2) );
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


double SensorNetwork::getDistFromBS(Node * which)
{

  return dist(which->x,which->y,baseStation.x,baseStation.y);
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int getCluster(int sector, int slice)
{
   return sector*8+slice;
}



} /* end of namespace Simulator */

} /* end of WSN namespace */




