#ifndef __WSN_GUI_WSNSIM_H__
#define __WSN_GUI_WSNSIM_H__

#include <QMessageBox>
#include <QVector>
#include <QHash>
#include <QGraphicsPolygonItem>


#include "simulator/nodes/discrete_sim.h"

#include "simulator/sensor_network.h"
#include "simulator/discrete_simulator.h"
#include "simulator/node.h"

#include "ui_wsnsim.h"

namespace WSN
{

namespace GUI
{

class WSNsim : public QMainWindow, private Ui::WSNsim
{
  Q_OBJECT

  public:         /* class specific */
  
  WSNsim();
  ~WSNsim();

  private slots: 

  void incrementTimeStep();
  void updateScene();


  private: /* methods */
  
  /* graphics */
  void setupScene();
  void setupSWebLines();
  QPolygonF makeCircle(qint32 segments, qreal radius);
  QGraphicsSimpleTextItem * timerItem;
  qreal penWidth;
  QPen getPen(const QColor& c, qreal width = -1);
  
  private:        /* variables */

  /* graphics */
  QGraphicsScene * scene;
  QVector<const Simulator::Nodes::DiscreteSim *> sensorNetworkNodes;
  QHash<const Simulator::Nodes::DiscreteSim *, QGraphicsPolygonItem *> polyHash;
  QHash<const Simulator::Nodes::DiscreteSim *, QGraphicsPolygonItem *> backPolyHash;
  //QHash<QGraphicsPolygonItem *, const Simulator::Node*> nodeHash; /*FIXME do we really need two hashs? - rax*/
  QGraphicsItemGroup * swebLines;
  //QGraphicsItemGroup * sendingLines;
  QGraphicsItemGroup * sendingLine;
  
  /* simulator */
  Simulator::SensorNetwork * sensorNetwork; /*FIXME - this should be in the Discrete Simulator*/
  Simulator::DiscreteSimulator * simulator;

};

} /* end of GUI namespace */

} /* end of WSN namespace */
 
#endif

