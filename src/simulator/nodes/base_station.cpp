#include "base_station.h"


namespace WSN
{

namespace Simulator
{

namespace Node
{



BaseStation::BaseStation(int id, double x, double y) : DiscreteSim(DiscreteSim::BaseStation, id,x,y) {


}


BaseStation::~BaseStation() {


}


int BaseStation::getNextHop() const {

  return 10; /*FIXME*/

}


} /* end of namespace Node */

} /* end of namespace Simulator */

} /* end of namespace WSN */
