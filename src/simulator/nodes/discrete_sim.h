#ifndef __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__
#define __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__

#include "../node.h"

namespace WSN
{

namespace Simulator
{

namespace Nodes
{


class DiscreteSim : public Node {

  public: /* class specific*/
  
  static const int numberOfPhases = 3;
  enum Type {Sensor, BaseStation};
  
  DiscreteSim(Type type, int id = 0, double x = 0, double y = 0, Node::State state = Idle);
  ~DiscreteSim();
  
  
  private: /* overridden methods (public -> private) */
  void setState(State state);
  
  public: /* methods */
  
  void doTimeStep(int phase);
  
  private: /* methods */
  
  void stateSetupPhase();
  void hardwareSimPhase();
  void stateUpdatePhase();
  
  public: /* variables */
  int energyRemaining;
  Type type;
  
  protected: /* variables */
  Node::State nextState;
  
  int sendReceiveTimer;
  int headAllocTimer;
  
  DiscreteSim* otherNode; /* depending on state, could represent the node that this node is sending to or receiving from*/

};


} /* end of namespace Nodes */

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
