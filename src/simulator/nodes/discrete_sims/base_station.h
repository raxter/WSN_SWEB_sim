#ifndef __WSN_SIMULATOR_NODE_DISCRETE_SIM_BASESTATION_H__
#define __WSN_SIMULATOR_NODE_DISCRETE_SIM_BASESTATION_H__

#include "../discrete_sim.h"

#include <vector>

namespace WSN
{

namespace Simulator
{

namespace Nodes
{

namespace DiscreteSims
{


class BaseStation : public DiscreteSim {

  public: /* class specific */

  BaseStation(double x = 0, double y = 0);
  ~BaseStation();

  
  public: /* overridden methods */
  
  Node * getNextHop() const ;
  
  
  std::vector<Nodes::DiscreteSim * > sectionHeadNodes;

};


} /* end of namespace DiscreteSims */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */



#endif /* __SIMULATOR_BASESTATION _H__ */

