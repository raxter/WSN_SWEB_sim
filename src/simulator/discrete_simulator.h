#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__


namespace WSN
{

namespace Simulator
{

class DiscreteSimulator  {

  public:



  ///Constructors/Destructors
  DiscreteSimulator();
  ~DiscreteSimulator();
  
  unsigned long currentTime();

  private:
  
  unsigned long currentTime;// in milliseconds

};


} /* end of namespace Simulator */


} /* end of namespace WSN */

















#endif
