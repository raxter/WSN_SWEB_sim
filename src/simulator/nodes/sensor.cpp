#include "sensor.h"


namespace WSN
{

namespace Simulator
{

namespace Node
{



Sensor::Sensor(int id, double x, double y) : DiscreteSim(DiscreteSim::Sensor, id,x,y) {


}


Sensor::~Sensor() {


}


int Sensor::getNextHop() const {

  return 0; /*FIXME*/

}


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */
