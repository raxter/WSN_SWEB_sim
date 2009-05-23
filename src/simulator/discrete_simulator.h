#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__

#include "sensor_network.h"
#include <QObject>
#include <QVector>
#include <QThread>
#include <QMutex>

namespace WSN
{

namespace Simulator
{

class DiscreteSimulator : public QThread  {

  Q_OBJECT

  public: /* class specific */
  ///Constructors/Destructors
  DiscreteSimulator(SensorNetwork * sensorNetwork);
  ~DiscreteSimulator();

  signals:

  void logEvent( const QString & event );
  void finishedTimeStep ();
  

  public: /* methods */
  void requestStopRunning();

  unsigned long currentTime();

  private: /* methods */
  
  void run();

  void incrementTimeStep();

  void timeStepCompleted(); // notification that a time step has been completed TODO should this be in SensorNetwork?
  void incrementTimeStep(Node::DiscreteSim * node);

  private: /* variables */
  
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
