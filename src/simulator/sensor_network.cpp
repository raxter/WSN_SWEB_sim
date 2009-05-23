#include "sensor_network.h"


#include <cstdlib>
#include <cmath>
#include <iostream>
#include <typeinfo>

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


SensorNetwork::SensorNetwork(int xRangeIn, int yRangeIn, int numberOfNodes, int numberOfSectors) :
      baseStation(),
      numberOfSectors(numberOfSectors),
      numberOfNodes(numberOfNodes),
      scanAngle(360.0/numberOfSectors)
{
  createNodes(xRangeIn,yRangeIn);

  init();

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
SensorNetwork::~SensorNetwork()
{
  for (int c = 0 ; c < sensors.size(); c++)
    delete sensors[c];
  delete baseStation;

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


void SensorNetwork::createNodes(int x , int y)
{
  baseStation = new Node::BaseStation();
  srand(0);
  //cout<<"start of createNodes "<<numNodes<<endl;
  for (int a = 0 ; a < numberOfNodes ; a++)
  {
      int randx = x/2 - rand()%(x+1);
      int randy = y/2 - rand()%(y+1);
      sensors.push_back( new Node::Sensor(a+1, randx, randy));

  }
  //cout<<"end of createNodes "<<numNodes<<endl;
}




/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::determineCluster(const Node::Sensor * in) const
{
  double x = in->x();
  double y = in->y();

  double dist = getDistFromBS(in);
  int degreesOutward = (int)dist/(int)threshDegree;

  int relSlice = getSlice(x , y);

  int output = degreesOutward*numberOfSectors + relSlice;

  return degreesOutward*numberOfSectors + relSlice;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

const Node::Sensor* SensorNetwork::getSensor(int id) const {
  return sensors[id];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::getSlice(double x , double y) const
{

  double angle=0 ;
  if  (x*y > 0)
  {
      angle = atan((abs(y)+0.0)/(abs(x)+0.0));
      if (y<0)
          angle = angle + M_PI;
  }
  else if (x*y < 0)
  {
      angle = atan((y+0.0)/(-x+0.0));
      if (y>0)
          angle = M_PI - angle;
      else
          angle = 2*M_PI - angle;
  }
  else if (x==0)
      if (y>0)
          angle = M_PI/2;
      else if (y < 0)
          angle = 3*M_PI/2;
      else angle = -1;
  else
  {
      if (x>0)
          angle = 0;
      else if (x < 0)
          angle = -1*M_PI;
      else angle = -1;
  }
  angle = angle *180/M_PI;

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
/*Node * SensorNetwork::nextHop (Node * source)
{
  if (source == &baseStation)
      return source;

  else if (source->isHead()) ///route to next cluster head
  {
    ///Get the next nearest head node: contenders are [0][0], [0][1] and [0][2] if they exist

    int nextClusterNo = source->getRouteTable(0,1);//ur here




    if (nextClusterNo == -1)
      return &baseStation;
    else
      return clusterHeads[nextClusterNo];

  }
  else ///route to head node of cluster
  {
      return clusterHeads[source->getCluster()];
  }
}*/


/****************************************************************************
**
** Author: Richard Baxter
**
** returns all sensors and the baseStation(s)
**
****************************************************************************/

std::vector <Node::DiscreteSim *> SensorNetwork::getSimNodePointers()
{
  std::vector <Node::DiscreteSim *> out;
  out.push_back(baseStation);
  for (int a = 0 ; a < numberOfNodes ; a++) {
    out.push_back(sensors[a]);
  }
  cout << endl;
  return out;
}

/****************************************************************************
**
** Author: Richard Baxter
**
** returns all sensors and the baseStation(s)
**
****************************************************************************/

std::vector <const Node::DiscreteSim *> SensorNetwork::getConstSimNodePointers() const
{
  std::vector <const Node::DiscreteSim *> out;

  out.push_back(baseStation);
  for (int a = 0 ; a < numberOfNodes ; a++) {
    out.push_back(sensors[a]);

  }
  return out;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double SensorNetwork::getScanAngle() const {
  return scanAngle;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double SensorNetwork::getThreshDegree() const {
  return threshDegree;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


void SensorNetwork::init() {
  scanAngle = 360.0/numberOfSectors;
  threshDegree = 25;

  baseStation->numberOfSectors = numberOfSectors;
  baseStation->threshDegree = threshDegree;
  baseStation->numberOfNodes = numberOfNodes;
  baseStation->numberOfSectors = numberOfSectors;
  //baseStation->sendEnergy = ;
  

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ///determine number of clusters

  // determining the nodes' cluster numbers and finding out the number of total clusters
  /*numberOfClusters = 0;
  for (int a = 0 ; a < numberOfNodes ; a++) {
      int cluster = determineCluster(sensors[a]);
      sensors[a]->setCluster(cluster);

      if (numberOfClusters < cluster+1)
        numberOfClusters = cluster+1;
  }

  typedef std::vector <Node::Sensor*> ClusterVec;

  std::vector <ClusterVec> clusters(numberOfClusters);

  ///determine all nodes clusters
  for (int a = 0 ; a < numberOfNodes ; a++) {
      int cluster = sensors[a]->getCluster();
      clusters[cluster].push_back(sensors[a]);
  }

  ///set initial cluster heads
  for (int b = 0 ; b < numberOfClusters ; b++)
  {
    ClusterVec &cluster = clusters[b];
    //cout <<"size: "<< cluster.size()<< endl;

    int highestRemEnergy = 0;
    SensorNode * newHead = NULL;
    for (int c = 0 ; c < cluster.size(); c++)
    {
        //cout << "there are actual nodes in this cluster: "<< " current node in cluster: "<<cluster[c]->cluster<<endl;
        if (cluster[c]->energyRemaining > highestRemEnergy)
        {
            highestRemEnergy = cluster[c]->energyRemaining;
            newHead = cluster[c];
            //cluster[c]->setHead(&newHead);
        }
    }
    for (int d = 0 ; d < cluster.size() ; d++)
      cluster[d]->setHead(newHead);


    clusterHeads.push_back(newHead);
    //cout<<"cluster "<<b<<" headnode "<<newHead<<endl;

  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  //for (int hnC = 0 ; hnC < clusterHeads.size() ; hnC++)
  //    cout<<"clust no: "<<hnC<<" CH: "<<getCluster(hnC).size()<<" - "<<clusterHeads[hnC]<<endl;

  ///since head nodes have been determined
  ///create routing tables
  for (int c = 0 ; c < numberOfNodes ; c++)
  {
      double dist = getDistFromBS(sensors[c]);
      int degreesOutward = (int)dist/(int)threshDegree;

      int relCluster = sensors[c]->getCluster();
      ///---------------------------------------------------------------------
      ///[2][2]:
      int c22 = (relCluster+1)%numberOfSectors + (degreesOutward+1)*numberOfSectors;
      Nodes::DiscreteSim * c22Head ;
      if (c22 > numberOfClusters)
        c22Head = NULL;
      else
        c22Head = clusterHeads[c22];
      //assignNodeToRouteTable(&c22Head,c22);

      ///---------------------------------------------------------------------
      ///[2][1]:
      int c21=0;
      Nodes::DiscreteSim * c21Head;
      if (relCluster == 0 )
        c21 = 2*numberOfSectors-1;
      else
        c21 = relCluster+numberOfSectors;


      if (c21 > numberOfClusters)
        c21Head = NULL;
      else
        c21Head = clusterHeads[c21];

      ///---------------------------------------------------------------------
      ///[2][0]:
      int c20 = (relCluster-1)%numberOfSectors + (degreesOutward+1)*numberOfSectors;
      Nodes::DiscreteSim * c20Head;
       if (c20 > numberOfClusters)
        c20Head = NULL;
      else
        c20Head = clusterHeads[c20];

      ///---------------------------------------------------------------------
      ///[1][2]:
      int c12 = (relCluster +1)%numberOfSectors + degreesOutward*numberOfSectors;
      Nodes::DiscreteSim * c12Head;
       if (c12 > numberOfClusters)
        c12Head = NULL;
      else
        c12Head = clusterHeads[c12];

      ///---------------------------------------------------------------------
      ///[1][0]:
      int c10=0;
      Nodes::DiscreteSim * c10Head;
      if (relCluster == 0 )///special case where cluster num = 0
        c10 = numberOfSectors;
      else
        c10 = (relCluster -1)%numberOfSectors + degreesOutward*numberOfSectors;

      if (c10 > numberOfClusters)
          c10Head = NULL;
        else
          c10Head = clusterHeads[c10];

      ///---------------------------------------------------------------------
      ///[0][*]
      int c02,c01,c00 = 0;
      Nodes::DiscreteSim * c02Head, * c01Head, *c00Head;
      if (relCluster < numberOfSectors)
      {
          ///[0][2]:
          //c02 = -1;///-1 = base station
          c02Head = baseStation;
          ///[0][1]:
          //c01 = -1;///-1 = base station
          c01Head = baseStation;
          ///[0][0]:
          //c00 = -1;///-1 = base station
          c00Head = baseStation;
      }
      else
      {
          ///[0][2]:
          c02 = (relCluster+1)%numberOfSectors + (degreesOutward-1)*numberOfSectors;
          c02Head = clusterHeads[c02];
            ///[2][1]:
          c01 = relCluster-numberOfSectors;
          c01Head = clusterHeads[c01];
          ///[2][0]:
          c00 = (relCluster-1)%numberOfSectors + (degreesOutward-1)*numberOfSectors;
          c00Head = clusterHeads[c00];
      }

      //sensors[c].setRouteTable(c22Head,c21Head,c20Head,c12Head,c10Head,c02Head,c01Head,c00Head) ;
      //cout <<"clust of "<< c01Head->cluster<<endl;
      sensors[c]->setRouteTable(c22Head,c21Head,c20Head,c12Head,c10Head,c02Head,c01Head,c00Head) ;
      //cout<<"nodes ["<<c<<"] cl: "<<sensors[c].cluster<<endl;
      //sensors[c].printTable();


  }
  
  baseStation->targetNode = sensors[10];
  baseStation->initiate();
  */
  /*cout <<  numberOfSectors << endl << endl;
  for (int i = 0 ; i < numberOfSectors; i++) {
    baseStation->sectionHeadNodes.push_back(clusterHeads[i]);
    cout <<  (clusterHeads[i]?clusterHeads[i]->getId():-1) << endl;
  }*/

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
/*void SensorNetwork::assignNodeToRouteTable(SensorNode * nodeIn, int clusterNo)
{
  if (clusterNo > numberOfClusters)
        nodeIn = NULL;
        else
        nodeIn = clusterHeads[clusterNo];
}*/


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


double SensorNetwork::getDistFromBS(const Node::Sensor * node) const
{

  return dist(node->x(),node->y(),baseStation->x(),baseStation->y());
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::getCluster(int sector, int slice)
{
   return sector*numberOfSectors+slice;
}



} /* end of namespace Simulator */

} /* end of WSN namespace */



