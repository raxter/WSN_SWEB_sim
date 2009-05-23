
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

    // Node* nextHop(Node * source); /*needs to move to Node class, see cpp file - rax*/
    const Node::Sensor* getSensor(int id) const;

    std::vector <Node::DiscreteSim *> getSimNodePointers();
    std::vector <const Node::DiscreteSim *> getConstSimNodePointers() const;

    double getScanAngle() const;
    double getThreshDegree() const;


  private: /* methods */


    void    init();
    void    createNodes(int x,int y);

    int     getClusterNo (int sector, int slice);
    int *   getClusterCoor(int cluNo);
    int     getSlice(double x , double y) const;

    double  dist(int x1, int y1, int x2, int y2) const; /* make a static function ?*/
    double  getDistFromBS(const Node::Sensor * which) const;
    int     determineCluster(const Node::Sensor * in) const;
    int     getCluster(int sector, int slice);
    //void    assignNodeToRouteTable(Node::Sensor * nodeIn, int clusterNo);

  public: /* variables */
    int numberOfSectors;


  private: /* variables */

    std::vector <Node::Sensor*> clusterHeads; /*TODO shouldn't be here - rax*/
    std::vector <Node::Sensor*> sensors; /*NOTE sensors are now stored dynamically so that the vtable look up will work*/
    Node::BaseStation * baseStation;

    double scanAngle;
    double threshDegree;

    int numberOfNodes;
    int numberOfClusters; /*TODO what's this do? - rax*/
};

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif

