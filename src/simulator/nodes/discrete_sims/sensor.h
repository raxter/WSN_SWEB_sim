#ifndef __WSN_SIMULATOR_NODE_DISCRETE_SIM_SENSOR_H__
#define __WSN_SIMULATOR_NODE_DISCRETE_SIM_SENSOR_H__

#include  "../discrete_sim.h"
#include  "base_station.h"

namespace WSN
{

namespace Simulator
{

namespace Nodes
{

namespace DiscreteSims
{


class Sensor : public DiscreteSim {

  public:

    ///Constructors/Destructors
    Sensor(int id = 0, double x = 0, double y = 0);
    ~Sensor();

  public: /* overridden methods */
    Node * getNextHop();

  public: /* methods */

    void printTable() const;

    int getCluster() const;
    void setCluster(int cluster);

    bool isHead() const;
    void setHead(DiscreteSim * nodeId);
    DiscreteSim * getHead() const;

    void setRouteTable(DiscreteSim * c22, DiscreteSim * c21,DiscreteSim * c20,DiscreteSim * c12,DiscreteSim * c10, DiscreteSim * c02,DiscreteSim * c01,DiscreteSim * c00);

  private: /* methods */
    void init();

    DiscreteSim * getRouteTable(int row, int col) const;

  private: /* variables */

    int cluster;
    Nodes::DiscreteSim * routeTable [3][3];

  public: /* variables */
    Nodes::DiscreteSims::BaseStation * baseStation;


};


} /* end of namespace DiscreteSims */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
