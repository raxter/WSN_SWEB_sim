#ifndef __WSN_SIMULATOR_NODE_BASE_STATION_H__
#define __WSN_SIMULATOR_NODE_BASE_STATION_H__

#include "discrete_sim.h"
#include "physical_layer.h"
#include "base_station_layers/link.h"
#include "base_station_layers/network.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

class BaseStation : public PhysicalLayer, public BaseStationLayers::Link, public BaseStationLayers::Network {

  public: /* class specific*/

    BaseStation(int id = -1, double x = 0, double y = 0);
    virtual ~BaseStation();
    
  protected: /* overridden methods */

    void setUpPhase ();
    void wrapUpPhase ();
    
  public: /* overridden methods */

};


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
