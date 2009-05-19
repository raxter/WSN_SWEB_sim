#ifndef __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__
#define __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__

#include "../node.h"

#include "simulator/packet.h"

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
  
  
  protected: /* overridden methods */
  void setState(State state);
  
  public: /* methods */
  
  const DiscreteSim * getOtherNode() const;
  void doNextPhaseOfTimeStep();
  const Packet * getPacket() const;
  
  double getPercentageDone() const;
  
  private: /* methods */
  
  void stateSetupPhase();
  void hardwareSimPhase();
  void stateUpdatePhase();
  
  protected: /* methods */
  
  virtual void stateIdle();
  virtual void stateSending();
  virtual void stateReceiving();
  virtual void stateReadyToSend();
  virtual void stateOutOfEnergy();
  
  void packetReceiveStart();
  virtual void packetReceiveFinished(Packet * packet);
  virtual void packetSendStart();
  void packetSendFinish();
  
  
  public: /* variables */
  
  int energyRemaining;
  Type type;
  
  protected: /* variables */
  Packet * packet;
  private: /* variables */
  
  int phase;
  
  Node::State nextState;
    
  DiscreteSim* otherNode; /* depending on state, could represent the node that this node is sending to or receiving from*/
  
  /* state == Node::Sending specific */
  int sendTimer;
  int sendTimerTotal;
  
  //int headAllocTimer; /* for head cluster reorganisation */

};


} /* end of namespace Nodes */

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
