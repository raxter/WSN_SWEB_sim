#include "sensor.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{



Sensor::Sensor(int id, double x, double y) : DiscreteSim(DiscreteSim::Sensor, id,x,y) {

 // std::cout << "Sensor::Sensor(id = " << id << ", x = " << x << ", y = " << y << ")" << std::endl;
}


Sensor::~Sensor() {


}


int Sensor::getNextHop() const {

  /*if (id == 95) {
    std::cout << id << std::endl;

    for (int i = 0 ; i < 3 ; i++)
      std::cout << routeTable[i][0] << " \t " << routeTable[i][1] << " \t " << routeTable[i][2] << std::endl;
  }*/

  if (isHead()) ///route to next cluster head
  {
    ///Get the next nearest head node: contenders are [0][0], [0][1] and [0][2] if they exist

    int rightBelow = routeTable[0][0];
    int leftBelow = routeTable[0][2];
    bool rightBelowIsNull;
    bool leftBelowIsNull;


    if (rightBelow == -1)
      rightBelowIsNull = true;
    if (leftBelow == -1)
      leftBelowIsNull = true;


    ///the simple SWEB routing algorithm
    if (routeTable[0][1] != -1)
      return routeTable[0][1];
    else if ((!rightBelowIsNull) && (!leftBelowIsNull)) {
      if (dist(rightBelow, id) < dist(leftBelow, id))
        return rightBelow;
      else 
        return leftBelow;
    }
    else if (!rightBelowIsNull)
      return rightBelow;
    else if (!leftBelowIsNull)
      return leftBelow;
    else 
      return 0;


  }
  else ///route to head node of cluster
  {
      return routeTable[1][1];
  }

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
