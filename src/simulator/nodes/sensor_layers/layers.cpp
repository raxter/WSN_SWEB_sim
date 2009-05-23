




#include "layers.h"

#include <iostream>

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace SensorLayers
{


Layers::Layers() : currentNetworkState(NetworkUninitialised), currentLinkState(LinkUninitialised) {
}


Layers::~Layers() {

}


int Layers::calcThresh(int thresh, int receivedStrength) {
  return receivedStrength/thresh;
}

int Layers::calcGroupId(int threshId, int sectorId, int maxNumberOfSectors) {
  return threshId + (sectorId*maxNumberOfSectors);
}

int Layers::calcMaxNumberOfGroup(int thresh, int sendStrength, int numberOfSectors) {
  int maxThreshId = calcThresh(thresh, sendStrength);
  return numberOfSectors*maxThreshId;
}

} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */













