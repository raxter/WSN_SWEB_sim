#ifndef __WSN_SIMULATOR_NODE_PHYSICAL_LAYER_H__
#define __WSN_SIMULATOR_NODE_PHYSICAL_LAYER_H__

#include <list>
#include <vector>

#include "discrete_sim.h"

#include "../base_packet.h"

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

    void proxied_setUpPhase ();
    void physicalLayerSendLogic ();
    void physicalLayerReceiveLogic ();
    void proxied_wrapUpPhase ();

    bool inTimeSlot();
  public: /* methods */
  
  const BasePacket * getCurrentSendingPacket();

  protected: /* methods */

  private: /* methods */
  
  public: /* variables */

    enum ReceivingState {NotReceiving, Receiving, RejectReceive};
    ReceivingState receivingState;
    //int receivedPacketStrength;
    //const BasePacket * receivedPacket;
    
    bool packetSendingFinished;
    int bitsOfPacketSent;

  protected: /* variables */
    enum State {Phy_Idle, Phy_Receiving, Phy_Sending};
    State currentState, nextState;
    
    BasePacket * currentSendingPacket;
  
  
  private: /* variables */

};


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
