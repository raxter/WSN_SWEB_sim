#ifndef __WSN_SIMULATOR_NODE_BASE_STATION_LINK_LAYER_H__
#define __WSN_SIMULATOR_NODE_BASE_STATION_LINK_LAYER_H__

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


class Link : virtual public DiscreteSim, virtual public Layers {


  public: /* class specific*/

  Link();
  virtual ~Link();


  protected: /* overridden methods */
    void proxied_setUpPhase ();
    void linkLayerLogic ();
    void proxied_wrapUpPhase ();

  public: /* methods */

  private: /* methods */
  
  protected: /* methods */

  public: /* variables */
  int numberOfSectors;
  int threshDegree;
  int numberOfNodes;

  int WaitingForGroupInitsToFinish_timeout;
  int WaitingForGroupInitsToFinish_timer;

  protected: /* variables */
  
  
  private: /* variables */

};


} /* end of namespace BaseStationLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
