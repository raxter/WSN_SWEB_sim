#ifndef __WSN_SIMULATOR_NODE_SENSOR_NETWORK_LAYER_H__
#define __WSN_SIMULATOR_NODE_SENSOR_NETWORK_LAYER_H__

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

namespace SensorLayers
{

/* deals with routing*/
class Network : virtual public DiscreteSim, virtual public Layers {


  public: /* class specific*/

  Network();
  virtual ~Network();


  protected: /* overridden methods */
    void networkLayerLogic ();
    void proxied_setUpPhase ();
    void proxied_wrapUpPhase ();

  public: /* methods */
  
  bool isHead() const;

  private: /* methods */
  
  
  protected: /* methods */


  public: /* variables */


  int InitialisingGroup_timeout;
  int InitialisingGroup_timer;

  protected: /* variables */
  
  int routeTable [3][3];
  
  std::vector<const BaseNode*> groupNodes;
  
  private: /* variables */

};


} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
