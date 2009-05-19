


#include "base_station.h"

namespace WSN
{

namespace Simulator
{

namespace Nodes
{

namespace DiscreteSims
{


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseStation::BaseStation(double x , double y) : DiscreteSim(Nodes::DiscreteSim::BaseStation, -1, x, y, Node::ReadyToSend)
{
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseStation::~BaseStation()
{

}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/




/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

Node * BaseStation::getNextHop() const /*overloaded*/
{
  /* TODO implement routing for the base station*/
  return targetNode;
}



} /* end of namespace DiscreteSims */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */

