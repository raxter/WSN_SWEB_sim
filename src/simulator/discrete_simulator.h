#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__

#include "sensor_network.h"
#include "nodes/base_node.h"

#include "packets/init.h"
#include "packets/energy_req.h"
#include "packets/data_req.h"

#include <QVector>
#include <QThread>
#include <QMutex>
#include <QHash>
#include <QMetaType>

#include <iostream>

namespace WSN
{

namespace Simulator
{

struct Signal {
  
  Signal(Node::BaseNode * src = 0, Node::BaseNode * dst = 0, int amountSent = -1, const BasePacket * finishedPacket = 0) : 
      src(src), 
      dst(dst), 
      amountSent (amountSent), 
      finishedPacket(finishedPacket)
  {
    //std::cout << "finishedPacket " << finishedPacket << std::endl;
  }
  
  Node::BaseNode * src;
  Node::BaseNode * dst;
  int amountSent;
  const BasePacket * finishedPacket;
  
};

class DiscreteSimulator : public QThread  {

  Q_OBJECT

  public: /* class specific */
  ///Constructors/Destructors
  DiscreteSimulator(SensorNetwork * sensorNetwork);
  ~DiscreteSimulator();

  signals:

  void logEvent( const QString & event );
  void finishedTimeStep ();
  
  public slots:
  
  void lock();
  void unlock();

  void incrementTimeStep();

  public: /* methods */
  void requestStopRunning();

  unsigned long currentTime();
  
  const QVector<Signal>& getSignalList() const;

  private: /* methods */
  
  void run();

  void timeStepCompleted(); // notification that a time step has been completed TODO should this be in SensorNetwork?
  void incrementTimeStep(Node::DiscreteSim * node);

  private: /* variables */
  
  QVector<Signal> signalList;
  
  QHash<int, Node::BaseNode *> idToNode;
  QHash<int, QList<Node::BaseNode *> > groupIdToNodeList;
  QHash<int, QList<Node::BaseNode *> > sectorIdToNodeList;
  
  /* Thread */
  bool running;
  QMutex control;
  
  qreal speed; /* ms/s */
  qreal stepsToRun; /* ms */
  
  SensorNetwork * sensorNetwork;
  QVector<Node::DiscreteSim *> nodes;

  unsigned long _currentTime;// in milliseconds

};


} /* end of namespace Simulator */


} /* end of namespace WSN */

















#endif
