
#ifndef __WSN_SIMULATOR_SENSOR_NETWORK_H__
#define __WSN_SIMULATOR_SENSOR_NETWORK_H__

#include "nodes/discrete_sims/sensor.h"
#include "nodes/discrete_sims/base_station.h"

#include <vector>


namespace WSN
{

namespace Simulator
{

 /* so we don't have to go using namespace Node::DiscretelySimulated */
typedef Nodes::DiscreteSims::Sensor SensorNode;

class SensorNetwork {

public:
    ///Constructors & Destructors
    SensorNetwork(int xRangeIn = 100, int yRangeIn = 100, int noNodesIn = 100, int numberOfSectors = 16);

    ~SensorNetwork();



  public: /* methods */
  
    ///functions

    // Node* nextHop(Node * source); /*needs to move to Node class, see cpp file - rax*/
    const SensorNode* getSensor(int id) const;

    std::vector <Nodes::DiscreteSim *> getSimNodePointers();
    std::vector <const Nodes::DiscreteSim *> getConstSimNodePointers() const;

    double scanAngle() const;

    double threshDegree() const;
    

  private: /* methods */

    
    void    init();
    void    createNodes(int x,int y);
    
    std::vector <SensorNode *> getCluster(int clustNo);
    int     getClusterNo (int sector, int slice);
    int *   getClusterCoor(int cluNo);
    int     getSlice(double x , double y) const;
    
    double  dist(int x1, int y1, int x2, int y2) const; /* make a static function ?*/
    double  getDistFromBS(const SensorNode * which) const;
    int     determineCluster(const SensorNode * in) const;
    //void    assignNodeToRouteTable(SensorNode * nodeIn, int clusterNo);

  public: /* variables */
    int numberOfSectors;
  
  
  private: /* variables */
  
    std::vector < std::vector <SensorNode*> > clusters; /*TODO shouldn't be here - rax*/
    std::vector <SensorNode*> clusterHeads; /*TODO shouldn't be here - rax*/
    std::vector <SensorNode*> sensors; /*NOTE sensors are now stored dynamically so that the vtable look up will work*/
    Nodes::DiscreteSims::BaseStation * baseStation;
    
    double _scanAngle;
    double _threshDegree;

    int numberOfNodes;
    int clusterMax; /*TODO what's this do? - rax*/
};

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif

