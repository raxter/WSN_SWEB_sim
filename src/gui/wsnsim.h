#ifndef __WSN_GUI_WSNSIM_H__
#define __WSN_GUI_WSNSIM_H__

#include <QMessageBox>

#include "simulator/sensor_network.h"
#include "simulator/node.h"

#include <vector>

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
  
  
  private:        /* variables */

  QGraphicsScene * scene;
  
  Simulator::SensorNetwork * sensorNetwork;

};

} /* end of GUI namespace */

} /* end of WSN namespace */
 
#endif

