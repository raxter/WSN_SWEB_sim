#ifndef __WSN_SIMULATOR_NODE_SENSOR_LINK_LAYER_H__
#define __WSN_SIMULATOR_NODE_SENSOR_LINK_LAYER_H__

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


class Link : virtual public DiscreteSim, virtual public Layers {


  public: /* class specific*/

  Link();
  virtual ~Link();


  protected: /* overridden methods */
    void linkLayerLogic ();
    void proxied_setUpPhase ();
    void proxied_wrapUpPhase ();

  public: /* methods */

  private: /* methods */
  
  protected: /* methods */

  public: /* variables */

  protected: /* variables */
  
  
  
  private: /* variables */

};


} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
