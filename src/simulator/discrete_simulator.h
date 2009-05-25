#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__

#include "sensor_network.h"
#include "nodes/base_node.h"

#include "packets/init.h"
#include "packets/energy_req.h"
#include "packets/data_req.h"

#include <QSet>
#include <QThread>
#include <QVector>
#include <QMutex>
#include <QHash>
#include <QMetaType>

#include <iostream>

namespace WSN
{

namespace Simulator
{

struct Signal {
  
  
  Node::BaseNode * src;
  Node::BaseNode * dst;
  double pos [4];
  int amountSent;
  const BasePacket * finishedPacket;
  PacketTypes::Type type;
  
  Signal(Node::BaseNode * src = 0, Node::BaseNode * dst = 0, int amountSent = -1, const BasePacket * finishedPacket = 0, PacketTypes::Type type = PacketTypes::NoType) : 
      src(src), 
      dst(dst), 
      amountSent (amountSent), 
      finishedPacket(finishedPacket),
      type(type)
  {
    //std::cout << "finishedPacket " << finishedPacket << std::endl;
    if (src) {
      pos[0] = src->x();
      pos[1] = src->y();
    }
    if (dst) {
      pos[2] = dst->x();
      pos[3] = dst->y();
    }
  }
  
};

class DiscreteSimulator : public QThread  {

  Q_OBJECT

  public: /* class specific */
  ///Constructors/Destructors
  DiscreteSimulator(SensorNetwork * sensorNetwork);
  ~DiscreteSimulator();

  signals:

  void logEvent( const QString & event );
  void finishedTimeStep (const QVector<Simulator::Signal>& list);
  void tick( );
  void clearSignals();
  
  void timeUpdated ( int time );
  
  public slots:
  
  //void lock();
  //void unlock();
  
  
  void setSpeed( int sp );
  void limitedTimeSimulation( int ms);
  void startSimulation();
  void stopSimulation();

  private slots:
  void incrementTimeStep();

  public: /* methods */
  double getAverageBatteryLife();
  void requestStopRunning();

  unsigned long currentTime();
  
  //const QVector<Signal>& getSignalList() const;

  private: /* methods */
  
  void run();

  void timeStepCompleted(); // notification that a time step has been completed TODO should this be in SensorNetwork?
  void incrementTimeStep(Node::DiscreteSim * node);

  private: /* variables */
  bool doSimulation;
  bool doLimitedSimulation;
  QVector<Signal> signalList;
  
  QHash<int, Node::BaseNode *> idToNode;
  QHash<int, QList<Node::BaseNode *> > groupIdToNodeList;
  QHash<int, QList<Node::BaseNode *> > sectorIdToNodeList;
  
  /* Thread */
  bool running;
  QMutex control;
  
  int speed; /* ms/s */
  int stepsToRun; /* ms */
  
  SensorNetwork * sensorNetwork;
  QVector<Node::DiscreteSim *> nodes;

  unsigned long _currentTime;// in milliseconds

};


} /* end of namespace Simulator */


} /* end of namespace WSN */

















#endif
