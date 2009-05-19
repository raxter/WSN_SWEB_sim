#ifndef __WSN_GUI_WSNSIM_H__
#define __WSN_GUI_WSNSIM_H__

#include <QMessageBox>
#include <QVector>
#include <QHash>


#include "graphics_scene.h"
#include "graphics_view.h"


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


  private: /* methods */
  
  
  private:        /* variables */

  /* graphics */
  GraphicsView  * graphicsView;
  GraphicsScene * graphicsScene;
  
  /* simulator */
  Simulator::SensorNetwork * sensorNetwork;
  Simulator::DiscreteSimulator * simulator;

};

} /* end of GUI namespace */

} /* end of WSN namespace */
 
#endif

