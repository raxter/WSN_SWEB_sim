#ifndef __WSN_SIMULATOR_NODE_BASE_NODE_H__
#define __WSN_SIMULATOR_NODE_BASE_NODE_H__


namespace WSN
{

namespace Simulator
{

class SensorNetwork;
//#include "../sensor_network.h"

namespace Node
{


/* holds all specs of the node, signal send strength, bandwidth, location in space, energy levels etc*/
class BaseNode {

  public: /* class specific*/

    static const double bandwidth = 54; // kb/s

    /*enum State {
      Running,
      OutOfEnergy
    };*/


    BaseNode(int id = -1, double x = 0.0, double y = 0.0, long long energyRemaining = 1000000000/*nano joules*/);
    virtual ~BaseNode();


  public: /* methods */
    void setSensorNetwork(const Simulator::SensorNetwork * sensorNetwork);

    double x() const;
    double y() const;
    int getId() const; /* TODO remove this*/
    double  distTo(BaseNode * otherNode) const;


  protected: /* methods */


    double dist(int id1, int id2) const;

  public: /* variables */
    const Simulator::SensorNetwork * sensorNetwork;

    long long energyRemaining;
    int id; // this node's id, if id == -1 it means undefined


  protected: /* variables */

  private: /* variables */
    double _x,_y;

    //State reallocState; /* to be used to store the reallocation channel state (if we use the dual channel method for reallocation)*/



};


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
