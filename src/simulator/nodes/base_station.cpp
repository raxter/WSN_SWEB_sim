#include "base_station.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{



BaseStation::BaseStation(int id, double x, double y) : DiscreteSim(DiscreteSim::BaseStation, id,x,y) {


  //std::cout << "BaseStation::BaseStation(id = " << id << ", x = " << x << ", y = " << y << ")" << std::endl;
}


BaseStation::~BaseStation() {


}


int BaseStation::getNextHop() const {

  return 10; /*FIXME*/

}


void BaseStation::setUpPhase () {
  std::cout << "in BaseStation::setUpPhase ()" << std::endl;
  PhysicalLayer::proxied_setUpPhase ();
  BaseStationLayers::Link::proxied_setUpPhase ();
  BaseStationLayers::Network::proxied_setUpPhase ();
  DiscreteSim::setUpPhase ();
}

void BaseStation::wrapUpPhase () {
  std::cout << "in BaseStation::wrapUpPhase ()" << std::endl;
  PhysicalLayer::proxied_setUpPhase ();
  BaseStationLayers::Link::proxied_wrapUpPhase ();
  BaseStationLayers::Network::proxied_wrapUpPhase ();
  DiscreteSim::wrapUpPhase ();
}

} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */
