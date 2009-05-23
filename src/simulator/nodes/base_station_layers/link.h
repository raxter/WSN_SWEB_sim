#ifndef __WSN_SIMULATOR_NODE_BASE_STATION_LINK_LAYER_H__
#define __WSN_SIMULATOR_NODE_BASE_STATION_LINK_LAYER_H__

#include <list>
#include <vector>

#include "../discrete_sim.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace BaseStationLayers
{


class Link : virtual public DiscreteSim {


  public: /* class specific*/

  Link();
  virtual ~Link();


  protected: /* overridden methods */
    virtual void linkLayerLogic ();

  public: /* methods */

  private: /* methods */
  
  protected: /* methods */

  public: /* variables */


  protected: /* variables */
  enum State {Uninitialised, WaitingForGroupInitsToFinish, Initialised};
  State state;
  
  
  private: /* variables */

};


} /* end of namespace BaseStationLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
