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
    int getId() const;
    State state() const;
    double  distTo(Node * otherSensor) const;
    
  protected: /* methods */
    virtual void setState(State state);

  protected: /* variables */

    virtual Node * getNextHop() = 0;

    //Packet * packet;
    //Packet * headReallocPacket;


    int id; // this node's id, if id == -1 it means undefined
  private: /* variables */
    double _x,_y;

    State _state;

    //State reallocState; /* to be used to store the reallocation channel state (if we use the dual channel method for reallocation)*/



};


} /* end of namespace Simulator */


} /* end of namespace WSN */


#endif
