#ifndef __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__
#define __WSN_SIMULATOR_NODE_DISCRETELY_SIMULATED_H__

#include <list>
#include <vector>

#include "base_node.h"

#include "simulator/packet.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

/* holds all general information needed to discretely simulate the node*/
class DiscreteSim : public BaseNode {


  public: /* class specific*/

  static const int numberOfPhases = 5;
  enum Type {Sensor, BaseStation};

  DiscreteSim(Type type, int id, double x, double y);
  ~DiscreteSim();

  protected: /* class specific*/
  DiscreteSim();

  protected: /* overridden methods */

  public: /* methods */

  void doNextPhaseOfTimeStep();


  private: /* methods */

  virtual void setUpPhase ();
  virtual void physicalLayerLogic ();
  virtual void linkLayerLogic ();
  virtual void networkLayerLogic ();
  virtual void wrapUpPhase ();

  protected: /* methods */

  public: /* variables */
  const Type type; // basestation or sensor

  protected: /* variables */
  
  private: /* variables */

  int phaseOfSimulation;
  
  

};


} /* end of namespace Node */

} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
