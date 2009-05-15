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
  Node();
  ~Node();

  ///mem allocation


  ///attributes for simulation
  enum State {
    IDLE,
    SENDING,
    RECEIVING,
    READY_TO_SEND, /*alse serves as RECEIVED*/
    OUT_OF_ENERGY
  };

  State state;
  State nextState;
  Node* otherNode; /* depending on state, could represent the node that this node is sending to or receiving from*/
  int sendReceiveTimer;
  int headAllocTimer;

  //general attributes
  //Node nul;
  int id; // this node's id, if id == -1, it means this node is the base station, -2 means undefined

  int x,y; /* FIXME - doubles rather, perhaps (?) - raxter */
  int cluster;
  Node * routeTable [3][3];
  int energyRemaining;

  ///functions

  bool isHead() const;
  void setHead(Node * nodeId);
  Node * getHead();

  void init();
  Node * getNextHop();

  void setCluster(int cluIn);
  int getCluster();
  void setRouteTable(Node * c22, Node * c21, Node * c20,Node * c12, Node * c10, Node * c02, Node * c01, Node * c00);
  void printTable();
  Node * getRouteTable(int row, int col);
  void assignToRouteTable(int row, int col, Node * in);
};


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
