#include "sensor_network.h"

namespace WSN
{
namespace Simulator
{



/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
SensorNetwork::SensorNetwork()
{
    noNodes=100;
    createNodes(100,100);
    init();
}


/****************************************************************************
**
** Author: Julian Hulme
**
** TODO insert description
**
****************************************************************************/

SensorNetwork::SensorNetwork(int xRangeIn, int yRangeIn, int noNodesIn)
{

    noNodes = noNodesIn;
    createNodes(xRangeIn,yRangeIn);

    init();
}


/****************************************************************************
**
** Author: Julian Hulme
**
** TODO insert description
**
****************************************************************************/

int SensorNetwork::determineCluster(Node * in)
{
  int x = in->x;
  int y = in->y;
  //cout <<"x: "<<x<<" y: "<<y<<endl;
  double dist = getDistFromBS(in);
  int degreesOutward = (int)dist/(int)threshDegree;


  /* .. phew, this code looks ugly - raxter*/
  double angle=0 ;
  if  (x*y > 0) /* something'th quadrant etc */
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
  {
    if (y>0)
      angle = pi/2;
    else if (y < 0)
      angle = 3*pi/2;
    else angle = -1;
    
  }
  else
  {
    if (x>0)
      angle = 0;
    else if (x < 0)
      angle = -1*pi;
    else angle = -1;
  }
  angle = angle *180/pi;
  //cout<<angle<<angle;

  int relivantSlice = 0;
  while (angle >= scanAngle)
  {
    relivantSlice++;
    angle -= scanAngle;
  //    cout<<relivantSlice<<" "<<angle<<endl;

  }

//        int ret[2];
//        ret[0] = degreesOutward;
//        ret[1] = relivantSlice;

  int output = degreesOutward*360/scanAngle + relivantSlice;
  ///global degreesOutputMax used as a reference later as to how far the web goes
  if (clusterMax < output)
      clusterMax = output;
  ///
  return degreesOutward*360/scanAngle + relivantSlice;
}


/****************************************************************************
**
** Author: Julian Hulme
**
** TODO insert description
**
****************************************************************************/

Node SensorNetwork::nextHop(Node source, Node target) /*FIXME should be const or & or something*/
{
  if (source.isHead())
  {
    return Node(); ///replace with nearest Head node here

  }
  else
    return Node();
}


/****************************************************************************
**
** Author: Julian Hulme
**
** TODO insert description
**
****************************************************************************/


SensorNetwork::~SensorNetwork()
{
  /* TODO clean up created nodes*/
}


/****************************************************************************
**
** Author: Julian Hulme
**
** TODO insert description
**
****************************************************************************/

void SensorNetwork::init()
{
  BS = Node(0,0);
  scanAngle = 45;//*PI/180;
  threshDegree=25;
  clusterMax=0;

  for (int a = 0 ; a < noNodes ; a++)
  {
    nodes[a].cluster = determineCluster(&nodes[a]);
    std::cout<<nodes[a].x<<" "<<nodes[a].y<<" - "<<nodes[a].cluster<<std::endl;
  }

  for (int b = 0 ; b < clusterMax ; b++)
  {
    std::vector <Node*> cluster = getCluster(b);
    std::cout <<"size: "<< cluster.size()<<std::endl;

    int lowestRemEnergy = MAX_NODE_ENGERGY+1;
    Node * newHead;
    for (int c = 0 ; c < cluster.size(); c++)
    {
      std::cout << "b: "<<clusterMax<<" cluster: "<<cluster[c]->cluster<<std::endl;
      if (cluster[c]->energyRemaining < lowestRemEnergy)
      {
        lowestRemEnergy = cluster[c]->energyRemaining;
        newHead = cluster[c];
      }
    }
  }


}

/****************************************************************************
**
** Author: Julian Hulme
**
** returns all the nodes in cluster clustNo this sensor network (NOTE - private method!)
**
****************************************************************************/

std::vector <Node *> SensorNetwork::getCluster(int clusterNumber)
{
  std::vector <Node *> out;
  for (int a = 0 ; a < noNodes ; a++)
  {
    if (nodes[a].cluster == clusterNumber)
      out.push_back(&nodes[a]);
  }
  return out;
}

/****************************************************************************
**
** Author: Ricahrd Baxter
**
** returns all the nodes in this sensor network
**
****************************************************************************/


std::vector <Node const *> SensorNetwork::getAllNodes() const
{
  std::vector <Node const *> out;
  for (int a = 0 ; a < noNodes ; a++)
    out.push_back(&nodes[a]);
  return out;
}

/****************************************************************************
**
** Author: Julian Hulme
**
** Creates a node at (x,y)
**
****************************************************************************/

void SensorNetwork::createNodes(int x , int y)
{
  std::cout<<"start of createNodes "<<noNodes<<std::endl;
  for (int a = 0 ; a < noNodes ; a++)
  {

    int randx = x/2 - rand()%(x+1);
    int randy = y/2 - rand()%(y+1);
    nodes[a] = Node(randx,randy);

    //cout <<"here we are: "<<nodes[a].x<<""<<nodes[a].y<<endl;
  }
  std::cout<<"end of createNodes "<<noNodes<<std::endl;
}

/****************************************************************************
**
** Author: Julian Hulme
**
** returns distance btween two points
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
** returns distance btween from TODO something TODO to Node which
**
****************************************************************************/

double SensorNetwork::getDistFromBS(Node * which)
{
  return dist(which->x,which->y,BS.x,BS.y);
}



} /* end of namespace Simulator */

} /* end of WSN namespace */



