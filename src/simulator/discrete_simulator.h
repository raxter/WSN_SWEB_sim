#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__

#include "sensor_network.h"
//#include <>

namespace WSN
{

namespace Simulator
{

class DiscreteSimulator  {

 //Q_OBJECT

  public: /* class specific */
  ///Constructors/Destructors
  DiscreteSimulator(SensorNetwork * sensorNetwork);
  ~DiscreteSimulator();

  public: /* methods */
  void incrementTimeStep();
  
  unsigned long currentTime();

  private: /* methods */

    
  void timeStepCompleted(); // notification that a time step has been completed TODO should this be in SensorNetwork?
  void incrementTimeStep(Node & node);

  private: /* variables */
  SensorNetwork * sensorNetwork;

  unsigned long _currentTime;// in milliseconds

};


} /* end of namespace Simulator */


} /* end of namespace WSN */

















#endif
