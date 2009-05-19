#include "sensor_network.h"


#include <cstdlib>
#include <cmath>
#include <iostream>

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


SensorNetwork::SensorNetwork(int xRangeIn, int yRangeIn, int numberOfNodes, int noSectors) : 
      baseStation(), 
      numberOfSectors(numberOfSectors), 
      numberOfNodes(numberOfNodes), 
      _scanAngle(360.0/noSectors)
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

}




/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::determineCluster(SensorNode * in)
{
  double x = in->x();
  double y = in->y();

  double dist = getDistFromBS(in);
  int degreesOutward = (int)dist/(int)_threshDegree;

  int relSlice = getSlice(x , y);

  int output = degreesOutward*numberOfSectors + relSlice;

  ///global degreesOutputMax used as a reference later as to how far the web goes
  if (clusterMax < output)
      clusterMax = output;
  ///
  return degreesOutward*numberOfSectors + relSlice;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

const SensorNode* SensorNetwork::getSensor(int id) const {
  return &sensors[id];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/

int SensorNetwork::getSlice(double x , double y)
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
  while (angle >= _scanAngle)
  {
      relivantSlice++;
      angle -= _scanAngle;

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

std::vector <Nodes::DiscreteSim *> SensorNetwork::getSimNodePointers()
{
  std::vector <Nodes::DiscreteSim *> out;
  out.push_back(&baseStation);
  for (int a = 0 ; a < numberOfNodes ; a++)
    out.push_back(&sensors[a]);
  return out;
}

/****************************************************************************
**
** Author: Richard Baxter
**
** returns all sensors and the baseStation(s)
**
****************************************************************************/

std::vector <const Nodes::DiscreteSim *> SensorNetwork::getConstSimNodePointers() const
{
  std::vector <const Nodes::DiscreteSim *> out;

  out.push_back(&baseStation);
  for (int a = 0 ; a < numberOfNodes ; a++)
    out.push_back(&sensors[a]);
  return out;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double SensorNetwork::scanAngle() const {
  return _scanAngle;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double SensorNetwork::threshDegree() const {
  return _threshDegree;
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/


void SensorNetwork::init() {
  _scanAngle = 45;//*M_PI/180; /*FIXME, should be based on numberOfSectors, doesn't have to be radians though :) */
  _threshDegree=25;
  clusterMax=0;

  ///determine all nodes clusters
  for (int a = 0 ; a < numberOfNodes ; a++)
  {
      sensors[a].setCluster(determineCluster(&sensors[a]));
      //cout<<"node: "<<a<<" x: "<<sensors[a].x<<" y: "<<sensors[a].y<<" cluster "<<sensors[a].cluster<<endl;

  }
  //exit(-1);

  ///set initial cluster heads
  for (int b = 0 ; b <= clusterMax ; b++)
  {
    vector <SensorNode*> cluster = getCluster(b);
    //cout <<"size: "<< cluster.size()<< endl;

    int highestRemEnergy = 0;
    SensorNode * newHead = NULL;
    for (int c = 0 ; c < cluster.size(); c++)
    {
        //cout << "there are actual nodes in this cluster: "<< " current node in cluster: "<<cluster[c]->cluster<<endl;
        //cout << c << " " << cluster[c]->energyRemaining << " < " << highestRemEnergy << endl;
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
  //for (int hnC = 0 ; hnC < clusterHeads.size() ; hnC++)
  //    cout<<"clust no: "<<hnC<<" CH: "<<getCluster(hnC).size()<<" - "<<clusterHeads[hnC]<<endl;

  ///since head nodes have been determined
  ///create routing tables
  for (int c = 0 ; c < numberOfNodes ; c++)
  {
      double dist = getDistFromBS(&sensors[c]);
      int degreesOutward = (int)dist/(int)_threshDegree;

      int relCluster = sensors[c].cluster();
      ///---------------------------------------------------------------------
      ///[2][2]:
      int c22 = (relCluster+1)%numberOfSectors + (degreesOutward+1)*numberOfSectors;
      Nodes::DiscreteSim * c22Head ;
      if (c22 > clusterMax)
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


      if (c21 > clusterMax)
        c21Head = NULL;
      else
        c21Head = clusterHeads[c21];

      ///---------------------------------------------------------------------
      ///[2][0]:
      int c20 = (relCluster-1)%numberOfSectors + (degreesOutward+1)*numberOfSectors;
      Nodes::DiscreteSim * c20Head;
       if (c20 > clusterMax)
        c20Head = NULL;
      else
        c20Head = clusterHeads[c20];

      ///---------------------------------------------------------------------
      ///[1][2]:
      int c12 = (relCluster +1)%numberOfSectors + degreesOutward*numberOfSectors;
      Nodes::DiscreteSim * c12Head;
       if (c12 > clusterMax)
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

      if (c10 > clusterMax)
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
          c02Head = &baseStation;
          ///[0][1]:
          //c01 = -1;///-1 = base station
          c01Head = &baseStation;
          ///[0][0]:
          //c00 = -1;///-1 = base station
          c00Head = &baseStation;
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
      sensors[c].setRouteTable(c22Head,c21Head,c20Head,c12Head,c10Head,c02Head,c01Head,c00Head) ;
      //cout<<"nodes ["<<c<<"] cl: "<<sensors[c].cluster<<endl;
      //sensors[c].printTable();


  }

}


/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
void SensorNetwork::assignNodeToRouteTable(SensorNode * nodeIn, int clusterNo)
{
  if (clusterNo > clusterMax)
        nodeIn = NULL;
        else
        nodeIn = clusterHeads[clusterNo];
}

/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
vector <SensorNode *> SensorNetwork::getCluster(int clusterNumber)
{
  vector <SensorNode *> out;
  for (int a = 0 ; a < numberOfNodes ; a++)
  {
     if (sensors[a].cluster() == clusterNumber)
       out.push_back(&sensors[a]);
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
  srand(0);
  //cout<<"start of createNodes "<<numNodes<<endl;
  for (int a = 0 ; a < numberOfNodes ; a++)
  {

      int randx = x/2 - rand()%(x+1);
      int randy = y/2 - rand()%(y+1);
      sensors.push_back( SensorNode(a, randx, randy));

  }
  //cout<<"end of createNodes "<<numNodes<<endl;
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


double SensorNetwork::getDistFromBS(SensorNode * node)
{

  return dist(node->x(),node->y(),baseStation.x(),baseStation.y());
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




