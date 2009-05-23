#ifndef __WSN_SIMULATOR_NODE_BASE_STATION_NETWORK_LAYER_H__
#define __WSN_SIMULATOR_NODE_BASE_STATION_NETWORK_LAYER_H__

#include <list>
#include <vector>

#include "../discrete_sim.h"
#include "layers.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace BaseStationLayers
{


class Network : virtual public DiscreteSim, virtual public Layers {


  public: /* class specific*/

  Network();
  virtual ~Network();


  protected: /* overridden methods */
    void proxied_setUpPhase ();
    void networkLayerLogic ();
    void proxied_wrapUpPhase ();

  public: /* methods */


  private: /* methods */
  
  
  protected: /* methods */


  public: /* variables */


  protected: /* variables */
  
  
  private: /* variables */

};


} /* end of namespace BaseStationLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
