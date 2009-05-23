




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


int Layers::calcThresh(int thresh, int receivedDistance) {
  //std::cout << "thresh = " << thresh << "  receivedDistance = " << receivedDistance << "  receivedDistance/thresh = " << receivedDistance/thresh << std::endl;
  return receivedDistance/thresh;
}

int Layers::calcGroupId(int threshId, int sectorId, int numberOfSectors) {
  //std::cout << "threshId = " << threshId << "  sectorId = " << sectorId << "  maxNumberOfSectors = " << numberOfSectors << " threshId + (sectorId*maxNumberOfSectors) = " << (threshId + (sectorId*numberOfSectors)) << std::endl;
  return sectorId + (threshId*numberOfSectors);
}

int Layers::calcMaxNumberOfGroup(int thresh, int sendStrength, int numberOfSectors) {
  int maxThreshId = calcThresh(thresh, sendStrength);
  return numberOfSectors*maxThreshId;
}

} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */













