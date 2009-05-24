
#include "base_node.h"
#include <cmath>
#include "../sensor_network.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{




/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseNode::BaseNode(int id, double x, double y, long long energyRemaining) : id (id), _x(x), _y(y), energyRemaining(energyRemaining)  {
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseNode::~BaseNode(){

}


double BaseNode::dist(int id1, int id2) const {
  const BaseNode * n1 = sensorNetwork->getNodeWithId(id1);
  const BaseNode * n2 = sensorNetwork->getNodeWithId(id2);

  return SensorNetwork::dist(n1->x(), n1->y(), n2->x(), n2->y());
}

void BaseNode::setSensorNetwork(const Simulator::SensorNetwork * sensorNetwork) {
  this->sensorNetwork = sensorNetwork;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double BaseNode::x() const {
  return _x;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

double BaseNode::y() const {
  return _y;
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

int BaseNode::getId() const {
  return id;
}



/****************************************************************************
**
** Author: Julian Hulme
**
****************************************************************************/
double BaseNode::distTo(BaseNode * otherSensor) const {

  return sqrt(pow(otherSensor->_x-this->_x,2) + pow(otherSensor->_y-this->_y,2) );
}







} /* end of namespace Node */

} /* end of namespace Simulator */


} /* end of namespace WSN */



