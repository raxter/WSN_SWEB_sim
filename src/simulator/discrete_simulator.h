#ifndef __WSN_SIMULATOR_DISCRETESIMULATOR__
#define __WSN_SIMULATOR_DISCRETESIMULATOR__

#include "sensor_network.h"
#include <QObject>
#include <QVector>

namespace WSN
{

namespace Simulator
{

class DiscreteSimulator : public QObject  {

  Q_OBJECT

  public: /* class specific */
  ///Constructors/Destructors
  DiscreteSimulator(SensorNetwork * sensorNetwork);
  ~DiscreteSimulator();

  signals:

  void logEvent( const QString & event );
  void finishedTimeStep ();

  public slots:

  void incrementTimeStep();

  public: /* methods */

  unsigned long currentTime();

  private: /* methods */

  void timeStepCompleted(); // notification that a time step has been completed TODO should this be in SensorNetwork?
  void incrementTimeStep(Node * node);

  private: /* variables */
  SensorNetwork * sensorNetwork;
  QVector<Nodes::DiscreteSim *> nodes;

  unsigned long _currentTime;// in milliseconds

};


} /* end of namespace Simulator */


} /* end of namespace WSN */

















#endif
