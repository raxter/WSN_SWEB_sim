#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__

#include "sensor_network.h"

namespace WSN
{

namespace Simulator
{

class DiscreteSimulator  {

  public: /* class specific */
  ///Constructors/Destructors
  DiscreteSimulator(SensorNetwork * sensorNetwork);
  ~DiscreteSimulator();

  public: /* methods */
  void incrementTimeStep();
  
  unsigned long currentTime();

  private: /* methods */

  void incrementTimeStep(Node & node);

  private: /* variables */
  SensorNetwork * sensorNetwork;

  unsigned long _currentTime;// in milliseconds

};


} /* end of namespace Simulator */


} /* end of namespace WSN */

















#endif
