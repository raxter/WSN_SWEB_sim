
#ifndef __WSN_SIMULATOR_SENSOR_NETWORK_H__
#define __WSN_SIMULATOR_SENSOR_NETWORK_H__

#include "nodes/sensor.h"
#include "nodes/base_station.h"
#include "nodes/discrete_sim.h"

#include <vector>



namespace WSN
{

namespace Simulator
{


class SensorNetwork {

public:
    ///Constructors & Destructors
    SensorNetwork(int xRangeIn = 100, int yRangeIn = 100, int noNodesIn = 100, int numberOfSectors = 16);

    ~SensorNetwork();



  public: /* methods */

    ///functions

    const Node::Sensor* getSensor(int id) const;
    const Node::BaseNode *getNodeWithId(int id) const;

    std::vector <Node::DiscreteSim *> getSimNodePointers();
    std::vector <const Node::DiscreteSim *> getConstSimNodePointers() const;

    double getScanAngle() const;
    double getThreshDegree() const;

    int     getSlice(double x , double y) const;
    static double  dist(int x1, int y1, int x2, int y2);

  private: /* methods */


    void    init();
    void    createNodes(int x,int y);

    int     getClusterNo (int sector, int slice);
    int *   getClusterCoor(int cluNo);

    double  getDistFromBS(const Node::Sensor * which) const;
    int     determineCluster(const Node::Sensor * in) const;
    int     getCluster(int sector, int slice);

  public: /* variables */
    int numberOfSectors;

    int numberOfNodes;

  private: /* variables */

    std::vector <Node::Sensor*> sensors;
    Node::BaseStation * baseStation;

    double scanAngle;
    double threshDegree;

    int numberOfClusters; /*TODO what's this do? - rax*/
};

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif

