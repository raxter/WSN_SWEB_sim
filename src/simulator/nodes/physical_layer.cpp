#include "physical_layer.h"


#include<iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{


PhysicalLayer::PhysicalLayer() : currentState(Phy_Idle), packetSendingFinished (false), currentSendingPacket(0) {

}


PhysicalLayer::~PhysicalLayer(){

}

const BasePacket * PhysicalLayer::getCurrentSendingPacket() {
  const BasePacket * ret = currentSendingPacket;
  
  if (packetSendingFinished) {
    currentSendingPacket = 0;
  }
  
  return ret;
}


bool PhysicalLayer::inTimeSlot() {
  return true; /*FIXME*/
}


void PhysicalLayer::proxied_setUpPhase () {
  //std::cout << "in PhysicalLayer::proxied_setUpPhase ()" << std::endl;
  nextState = currentState;
  
  
  receivingState = NotReceiving;
  receivedPacketStrength = 0;
  receivedPacket = 0;
  hardwareIsSending = false;
}


void PhysicalLayer::physicalLayerSendLogic () {
  //std::cout << "in PhysicalLayer::physicalLayerSendLogic ()" << std::endl;
  if (receivingState == NotReceiving) {
    if (inTimeSlot() && !outgoingPacketQueue.empty()) {
        
      if (!currentSendingPacket) {
        bitsOfPacketSent = 0;
        packetSendingFinished = false;
      }
      
      currentSendingPacket = outgoingPacketQueue.front();

      bitsOfPacketSent += bandwidth/**1000/1000*/; // kb/s -> b/ms
      
      if (bitsOfPacketSent > currentSendingPacket->getSizeInBytes()) {
        // then the packet has finished sending
        packetSendingFinished = true;
        outgoingPacketQueue.pop_front();
      }
      /*TODO energy calcs*/
      nextState = Phy_Sending;
      hardwareIsSending = true;
    }
    else {
      nextState = Phy_Idle;
    }
  }
  DiscreteSim::physicalLayerSendLogic ();
}

void PhysicalLayer::physicalLayerReceiveLogic () {
  //std::cout << "in PhysicalLayer::physicalLayerReceiveLogic ()" << std::endl;
  
  //if (receivedPacket) {
    /*FIXME - can't talk to link layer!*/
    //DiscreteSim::receivedPacket = receivedPacket;
    //DiscreteSim::receivedPacketStrength = receivedPacketStrength;
  //}
  
  if (receivingState == Receiving) {
    nextState = Phy_Receiving;
    /*TODO energy calcs*/
  
  }
  if (receivingState == RejectReceive) {
    nextState = Phy_Receiving;
    /*TODO energy calcs*//*IGNORE*/
  }
}
    


void PhysicalLayer::proxied_wrapUpPhase () {
  //std::cout << "in PhysicalLayer::proxied_wrapUpPhase ()" << std::endl;
  currentState = nextState;
}




} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */



