#ifndef __WSN_SIMULATOR_NODE_BASE_STATION_LAYERS_LAYERS_H__
#define __WSN_SIMULATOR_NODE_BASE_STATION_LAYERS_LAYERS_H__

#include <list>
#include <vector>

#include "../discrete_sim.h"

namespace WSN
{

namespace Simulator
{

namespace Node
{

namespace BaseStationLayers
{


class Layers : virtual public DiscreteSim {


  public: /* class specific*/

  Layers();
  virtual ~Layers();


  protected: /* overridden methods */

  public: /* methods */

  private: /* methods */
  
  protected: /* methods */

  public: /* variables */

  protected: /* variables */
  enum NetworkState {NetworkUninitialised, WaitingForReply, Running};
  NetworkState currentNetworkState, nextNetworkState;
  enum LinkState {LinkUninitialised, WaitingForGroupInitsToFinish, Initialised};
  LinkState currentLinkState, nextLinkState;
  
  int maxNumberOfIds;
  int sectorId;
  int maxNumberOfSectors;
  int threshId;
  int grpId;
  int maxNumberOfGroups;
  
  static int calcThresh(int thresh, int receivedStrength);
  static int calcGroupId(int threshId, int sectorId,int maxNumberOfSectors);
  static int calcMaxNumberOfGroup(int thresh, int sendStrength, int numberOfSectors);
  
  
  private: /* variables */

};


} /* end of namespace SensorLayers */

} /* end of namespace Nodes */

} /* end of namespace Simulator */

} /* end of namespace WSN */


#endif
