#ifndef __WSN_SIMULATOR_NODE_SENSOR_H__
#define __WSN_SIMULATOR_NODE_SENSOR_H__


#include "discrete_sim.h"
#include "physical_layer.h"
#include "sensor_layers/link.h"
#include "sensor_layers/network.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

class Sensor : public PhysicalLayer, public SensorLayers::Link, public SensorLayers::Network {

  public: /* class specific*/

    Sensor(int id = -1, double x = 0, double y = 0);
    virtual ~Sensor();
    
  protected: /* overridden methods */

    void setUpPhase ();
    void wrapUpPhase ();
    
  public: /* overridden methods */
  
    int getNextHop() const;

};


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
