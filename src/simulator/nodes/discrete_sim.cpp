
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

DiscreteSim::DiscreteSim(Type type, int id, double x, double y) : BaseNode(id,x,y), type(type), phaseOfSimulation(-1) {
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

DiscreteSim::DiscreteSim(): type(this->type) {

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
    case 0: setUpPhase();          break;
    case 1: physicalLayerLogic();  break;
    case 2: linkLayerLogic();      break;
    case 3: networkLayerLogic();   break;
    case 4: wrapUpPhase();         break;

  }
  
  if (phaseOfSimulation == numberOfPhases-1)
    phaseOfSimulation = -1;
}



void DiscreteSim::setUpPhase () {
}


void DiscreteSim::physicalLayerLogic () {
}


void DiscreteSim::linkLayerLogic () {
}


void DiscreteSim::networkLayerLogic () {
}


void DiscreteSim::wrapUpPhase () {
}





} /* end of namespace Node */

} /* end of namespace Simulator */


} /* end of namespace WSN */

