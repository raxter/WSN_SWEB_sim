
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

public:
    ///Constructors & Destructors
    SensorNetwork();
    SensorNetwork(int xRangeIn, int yRangeIn, int noNodesIn);
    ~SensorNetwork();


    ///mem alloaction
    std::vector <Node*> clusterHead;
    std::vector <Node> nodes;

    ///attributes
    Node BS;
    double scanAngle;
    int threshDegree;
    int noNodes;
    int clusterMax;

    ///functions

    Node* nextHop(Node * source);
    std::vector <Node *> getCluster(int clustNo);

    std::vector <const Node *> getNodePointers() const;

private:
    void init();
    void createNodes(int x,int y);
    int getClusterNo (int sector, int slice);
    int * getClusterCoor(int cluNo);
    int getSlice(int x , int y);
    double dist(int x1, int y1, int x2, int y2);
    double getDistFromBS(Node * which);
    int determineCluster(Node * in);


    ///temp
    void route();
};

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif

