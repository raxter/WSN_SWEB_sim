#ifndef __WSN_SIMULATOR_NODE_SENSOR_LAYERS_LAYERS_H__
#define __WSN_SIMULATOR_NODE_SENSOR_LAYERS_LAYERS_H__

#include <list>
#include <vector>

#include "../discrete_sim.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace SensorLayers
{


class Layers : virtual public DiscreteSim {


  public: /* class specific*/

  Layers();
  virtual ~Layers();


  protected: /* overridden methods */

  public: /* methods */
  static int calcThresh(int thresh, int receivedStrength);
  static int calcGroupId(int threshId, int sectorId,int maxNumberOfSectors);
  static int calcMaxNumberOfGroup(int thresh, int sendStrength, int numberOfSectors);

  private: /* methods */
  
  protected: /* methods */

  public: /* variables */
  int grpId;
  int sectorId;
  int threshId;
  int threshDegree;
  int numberOfSectors;

  enum NetworkState {NetworkUninitialised, InitialisingGroup, HeadReAlloc, HeadReAllocWait, Running};
  NetworkState currentNetworkState, nextNetworkState;
  enum LinkState {LinkUninitialised, Initialised};
  LinkState currentLinkState, nextLinkState;
  protected: /* variables */
  
  
  
  
  private: /* variables */

};


} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
