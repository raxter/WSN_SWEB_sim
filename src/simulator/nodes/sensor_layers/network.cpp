#include "network.h"



namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace SensorLayers
{


Network::Network(){

  for (int i = 0 ; i < 3 ; i++)
    for (int j = 0 ; j < 3 ; j++)
      routeTable[i][j] = 0;
}

Network::~Network(){}


void Network::networkLayerLogic (){}


bool Network::isHead() const {

  return this->id == routeTable[1][1];
}







} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */













