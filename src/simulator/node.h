#ifndef __WSN_SIMULATOR_NODE_H__
#define __WSN_SIMULATOR_NODE_H__

#include "constants.h"


#include <iostream>


namespace WSN
{

namespace Simulator
{

class Node  {

  public:

  ///Constructors/Destructors
  Node(int id, int x = 0, int y = 0);
  ~Node();

  ///mem allocation


  ///attributes for simulation
  enum State {
    IDLE, 
    SENDING, 
    RECEIVING, 
    READY_TO_SEND /*alse serves as RECEIVED*/, 
    OUT_OF_ENERGY
  };
  
  State state;
  State nextState;
  Node* otherNode; /* depending on state, could represent the node that this node is sending to or receiving from*/
  int timer;
  
  //general attributes
  
  int id; // this node's id, if id == -1, it means this node is the base station, -2 means undefined
  
  int x,y; /* FIXME - doubles rather, perhaps (?) - raxter */
  int cluster;
  int routeTable [3][3];
  int energyRemaining;

  ///functions
  bool isHead();
  void setHead(int nodeId);
  int getHead();

  void init();
  int getNextHop();
  void setCluster(int cluIn);
  int getCluster();
  void setRT(int  c22,int  c21,int  c20,int  c12, int  c10, int  c02, int  c01, int  c00);
  void printTable();
  int * getRT(int row);
};


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
