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
  
  Node * getNextHop();
  
  Node * targetNode; /*FIXME, this was just put in for testing*/
  
  protected: /* overridden methods */
  void stateIdle();
  void packetSendStart();
  void packetReceiveFinished(Packet * packet);

  public: /* methods */
  
  void initiate();

  protected: /* variables*/
  
  bool waitingForReply;

};


} /* end of namespace DiscreteSims */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */



#endif /* __SIMULATOR_BASESTATION _H__ */

