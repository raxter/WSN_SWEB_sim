#ifndef __WSN_SIMULATOR_SENSOR_NETWORK_H__
#define __WSN_SIMULATOR_SENSOR_NETWORK_H__

#include "node.h"
#include "constants.h"

#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

namespace WSN
{

namespace Simulator
{

class SensorNetwork {

  public: /*FIXME - need to do proper private, public and whatnot*/
    ///Constructors & Destructors
    SensorNetwork();
    SensorNetwork(int xRangeIn, int yRangeIn, int noNodesIn);
    ~SensorNetwork();

  private:

    ///mem alloaction
    std::vector <Node> clusterHead; /*FIXME should it not be Node * rather? - raxter*/
    Node nodes [1000];

    ///attributes
    Node BS;
    double scanAngle;
    int threshDegree;
    int noNodes;
    int clusterMax;

    ///functions
    
  public:
    std::vector <Node const *> getAllNodes() const;
    
    
  private:
    std::vector <Node *> getCluster(int clusterNumber);
    
    
    void init();
    
    void createNodes(int x,int y);
    
    double getDistFromBS(Node * which);
    double dist(int x1, int y1, int x2, int y2);
    
    int determineCluster(Node * in);
    Node nextHop(Node source, Node target);
    
    

};

} /* end of namespace Simulator */

} /* end of WSN namespace */


#endif

