#ifndef __WSN_SIMULATOR_NODE_PHYSICAL_LAYER_H__
#define __WSN_SIMULATOR_NODE_PHYSICAL_LAYER_H__

#include <list>
#include <vector>

#include "discrete_sim.h"

#include "simulator/packet.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{


class PhysicalLayer : virtual public DiscreteSim {


  public: /* class specific*/

    PhysicalLayer();
    virtual ~PhysicalLayer();


  protected: /* overridden methods */
    virtual void physicalLayerLogic ();

  public: /* methods */


  private: /* methods */
  
  
  protected: /* methods */


  public: /* variables */


  protected: /* variables */
    enum State {Idle, Receiving, Sending};
    State state;
  
  
  private: /* variables */

};


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
