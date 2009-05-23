
#include "base_node.h"
#include <cmath>

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

BaseNode::BaseNode(int id, double x, double y, long long energyRemaining) : id (id), _x(x), _y(y), energyRemaining(energyRemaining) {
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

BaseNode::~BaseNode(){

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



