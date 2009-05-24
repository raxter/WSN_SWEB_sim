
#include "discrete_sim.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim::DiscreteSim(Type type, int id, double x, double y) : BaseNode(id,x,y), type(type), phaseOfSimulation(-1), currentTime(0), linkLayerInitialised(false) {
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim::~DiscreteSim() {
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

DiscreteSim::DiscreteSim() : type(this->type) {

}


bool DiscreteSim::inTimeSlot(int estimatedMs) {
  int numberOfIds = maxNumberOfIds+1;
  
  int period = 40;//ms
  
  int oneWindow = numberOfIds*period;
  
  int positionInWindow = currentTime%oneWindow;
  
  int currentSlot = positionInWindow/period;
  
  
  
  //long long time = currentTime;
  //time /= period;
  
  //int slotUnMod = time/numberOfIds;
  
  //long long endOfSlot = (currentTime+1)/oneWindow*oneWindow;
  
  
  
  //if (currentTime + estimatedMs > endOfSlot)
   //  return false; // data will not be transmitted in time
  
  //else
  
  return currentSlot == id;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


//void DiscreteSim::setState(Node::State state) {
//  /* if during the setup of execute phase, use the nextState*/
//  if (phase < 4 && phase >= 0) {
//    nextState = state;
//  }
//  else /*otherwise if in the reset/update phase or not in the middle of simulation use the normal set menthod*/
//    Node::setState(state);
//}

/****************************************************************************
**
** Author: Richard Baxter
**
** calls this node to perform a specific phase of it's execution
**
****************************************************************************/

void DiscreteSim::doNextPhaseOfTimeStep() {

  phaseOfSimulation++;

  switch (phaseOfSimulation) {
    case 0: setUpPhase();                 break;
    case 1: physicalLayerSendLogic();     break;
    case 2: physicalLayerReceiveLogic();  break;
    case 3: linkLayerLogic();             break;
    case 4: networkLayerLogic();          break;
    case 5: wrapUpPhase();                break;

  }
  
  if (phaseOfSimulation == numberOfPhases-1)
    phaseOfSimulation = -1;
}



void DiscreteSim::setUpPhase () {
  //std::cout << "in DiscreteSim::setUpPhase ()" << std::endl;
}


void DiscreteSim::physicalLayerSendLogic () {
  //std::cout << "in DiscreteSim::physicalLayerSendLogic ()" << std::endl;
}

void DiscreteSim::physicalLayerReceiveLogic () {
  //std::cout << "in DiscreteSim::physicalLayerReceiveLogic ()" << std::endl;
}


void DiscreteSim::linkLayerLogic () {
  //std::cout << "in DiscreteSim::linkLayerLogic ()" << std::endl;
}


void DiscreteSim::networkLayerLogic () {
  //std::cout << "in DiscreteSim::networkLayerLogic ()" << std::endl;
}


void DiscreteSim::wrapUpPhase () {
  //std::cout << "in DiscreteSim::wrapUpPhase ()" << std::endl;
  currentTime++;
}





} /* end of namespace Node */

} /* end of namespace Simulator */


} /* end of namespace WSN */

