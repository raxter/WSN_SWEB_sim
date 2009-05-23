#ifndef __WSN_SIMULATOR_NODE_SENSOR_NETWORK_LAYER_H__
#define __WSN_SIMULATOR_NODE_SENSOR_NETWORK_LAYER_H__

#include <list>
#include <vector>

#include "../discrete_sim.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace SensorLayers
{

/* deals with routing*/
class Network : virtual public DiscreteSim {


  public: /* class specific*/

  Network();
  virtual ~Network();


  protected: /* overridden methods */
    virtual void networkLayerLogic ();

  public: /* methods */
  
  bool isHead() const;


  private: /* methods */
  
  
  protected: /* methods */


  public: /* variables */


  protected: /* variables */
  enum State {Uninitialised, HeadReAlloc, HeadReAllocWait, Running};
  State state;
  
  int routeTable [3][3];
  
  private: /* variables */

};


} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
