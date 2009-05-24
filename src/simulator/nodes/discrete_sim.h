#ifndef __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__
#define __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__

#include <list>
#include <vector>
#include <queue>

#include "base_node.h"

#include "../base_packet.h"
#include "../packets/init.h"
#include "../packets/grp_init.h"
#include "../packets/energy_req.h"
#include "../packets/data_req.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

/* holds all general information needed to discretely simulate the node*/
class DiscreteSim : public BaseNode {


  public: /* class specific*/

  static const int numberOfPhases = 6;
  enum Type {Sensor, BaseStation};

  DiscreteSim(Type type, int id, double x, double y);
  ~DiscreteSim();

  protected: /* class specific*/
  DiscreteSim();

  protected: /* overridden methods */

  public: /* methods */

  void doNextPhaseOfTimeStep();

  protected: /* methods */

  virtual void setUpPhase ();
  virtual void physicalLayerSendLogic ();
  virtual void physicalLayerReceiveLogic ();
  virtual void linkLayerLogic ();
  virtual void networkLayerLogic ();
  virtual void wrapUpPhase ();
  
  bool inTimeSlot(int estimatedMs = 0);
  
  private: /* methods */


  public: /* variables */
  const Type type; // basestation or sensor
  
  //NetworkSensorInfo& networkSensorInfo;
  
  int receivedPacketDistance;
  const BasePacket * receivedPacket;

  protected: /* variables */
  unsigned long long currentTime;
  int timeSlotId;
  
  int maxNumberOfIds;
  int maxNumberOfSectors;
  int maxNumberOfGroups;
  
  /* physical layer -> link layer info*/
  /* physical layer -> network layer info*/
  bool hardwareIsSending;
  
  /* link layer -> physical layer info*/
  std::deque<BasePacket *> outgoingPacketQueue;
  
  /* link layer -> network layer info*/
  bool linkLayerInitialised;
  
  
  private: /* variables */

  int phaseOfSimulation;
  
  

};


} /* end of namespace Node */

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
