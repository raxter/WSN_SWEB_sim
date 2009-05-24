#include "physical_layer.h"


#include<iostream>
#include <cmath>

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



void PhysicalLayer::proxied_setUpPhase () {
  //std::cout << "in PhysicalLayer::proxied_setUpPhase ()" << std::endl;
  nextState = currentState;


  receivingState = NotReceiving;
  receivedPacketDistance = 0;
  receivedPacket = 0;
  hardwareIsSending = false;
}


void PhysicalLayer::physicalLayerSendLogic () {
<<<<<<< HEAD:src/simulator/nodes/physical_layer.cpp
  std::cout << "in PhysicalLayer::physicalLayerSendLogic ()" << std::endl;
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
      std::cout << "type node "<<type<<std::endl;
      if (type == DiscreteSim::Sensor)
      {
      /// Energy loss
      /// assumptions are: timesteps are 1 msec each
      ///                  54 kb/s = 54 bits/msec transmission speed,
      ///                  50nJ/bit circuitry tax,
      ///                  100pJ / bit / m^2 sending transmission tax
      /// (see page 6/7 of SWEB doc)

      //std::cout << "dstID: "<<currentSendingPacket->dstId<<"getID: "<<getId()<<std::endl;
      //double dist = this->dist(getId(),currentSendingPacket->dstId);
      // std::cout << "hello"<<std::endl;
      double depletedCircuitryTax = 50/*nano J*/*54;
      std::cout << "type packet "<<currentSendingPacket->type<<std::endl;
      double depletedTransTax     = 100*pow(10,-3)/*nano J*/*54*pow(currentSendingPacket->signalDistance,2);
      std::cout << "depletedTransTax: "<<depletedTransTax<<std::endl;
      energyRemaining -= depletedCircuitryTax;
      energyRemaining -= depletedTransTax;

      //printf("energyRemaining%.10f\n",energyRemaining);
      std::cout << depletedTransTax<<std::endl<<depletedCircuitryTax<<std::endl <<receivedPacketDistance <<std::endl << energyRemaining<<std::endl;
      }
      nextState = Phy_Sending;
      hardwareIsSending = true;
=======
  
  //std::cout << "in PhysicalLayer::physicalLayerSendLogic ()" << std::endl;
  //if (inTimeSlot()) {
    //std::cout << "in timeslot " << id << " (" << currentTime << ")" << std::endl;
  //}
  if (receivingState == NotReceiving) {
    if (!outgoingPacketQueue.empty()) {
    
      if (inTimeSlot(outgoingPacketQueue.front()->getSizeInBytes()/bandwidth)) {
        //std::cout << "in timeslot " << id << std::endl;
        //std::cout << "curent time " << currentTime << std::endl;
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
      else { // not in time slot
        nextState = Phy_Idle;
      }
>>>>>>> 4d6c8db6ca3489d8dc0ca06751de06dba5d5b5ec:src/simulator/nodes/physical_layer.cpp
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
  if (type == DiscreteSim::Sensor)
  {
    double depletedCircuitryTax = 50/*nano J*/*54;
    energyRemaining -= depletedCircuitryTax;
  }
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



