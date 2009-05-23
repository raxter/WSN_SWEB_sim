#include "sensor.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{



Sensor::Sensor(int id, double x, double y) : DiscreteSim(DiscreteSim::Sensor, id,x,y) {
  
  std::cout << "Sensor::Sensor(id = " << id << ", x = " << x << ", y = " << y << ")" << std::endl;
}


Sensor::~Sensor() {


}


int Sensor::getNextHop() const {

  return 0; /*FIXME*/

}

void Sensor::setUpPhase () {
  
  //std::cout << "in Sensor::setUpPhase ()" << std::endl;
  PhysicalLayer::proxied_setUpPhase ();
  SensorLayers::Link::proxied_setUpPhase ();
  SensorLayers::Network::proxied_setUpPhase ();
  DiscreteSim::setUpPhase ();
}

void Sensor::wrapUpPhase () {
  //std::cout << "in Sensor::wrapUpPhase ()" << std::endl;
  PhysicalLayer::proxied_wrapUpPhase ();
  SensorLayers::Link::proxied_wrapUpPhase ();
  SensorLayers::Network::proxied_wrapUpPhase ();
  DiscreteSim::wrapUpPhase ();
}

} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */
