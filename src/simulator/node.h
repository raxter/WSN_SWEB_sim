#ifndef __WSN_SIMULATOR_NODE_H__
#define __WSN_SIMULATOR_NODE_H__


namespace WSN
{

namespace Simulator
{


class Node {

  public: /* class specific*/
  
  
  
    enum State {
      Idle,
      Sending,
      Receiving,
      ReadyToSend, /*also serves as Received*/
      OutOfEnergy
    };
    
    
    Node(int id = 0, double x = 0.0, double y = 0.0, State state = Idle);
    virtual ~Node();
  
  
  public: /* methods */
  
    double x() const;
    double y() const;
    virtual State state() const;
    virtual void setState(State state);
    
    const Node* otherNode() const;
    
    virtual Node * getNextHop() const = 0;
  
  protected: /* variables */
  
    int id; // this node's id, if id == -1 it means undefined
    double _x,_y;

    State _state;
    
    Node* _otherNode; /* depending on state, could represent the node that this node is sending to or receiving from*/
  


};


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
