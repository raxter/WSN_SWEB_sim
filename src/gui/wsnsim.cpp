#include "wsnsim.h"


#include <QDebug>

namespace WSN
{

namespace GUI
{



/****************************************************************************
**
** Author: Richard Baxter
**
** Default constructor
**
****************************************************************************/

WSNsim::WSNsim ()
{
  setupUi(this);      /* from ui_wsnsim.h: generated from wsnsim.ui */
  
  graphicsView = new GraphicsView();
  this->setCentralWidget(graphicsView);
  graphicsView->setDragMode ( QGraphicsView::ScrollHandDrag );
  
  
  sensorNetwork = new Simulator::SensorNetwork(100,100,100); /* FIXME paramaterise these 100's*/
  graphicsScene = new GraphicsScene(sensorNetwork );
  
  
  graphicsView->setScene ( graphicsScene );
  

  simulator = new Simulator::DiscreteSimulator(sensorNetwork);

  
  connect (stepButton, SIGNAL(released ()), this, SLOT(incrementTimeStep()));
  connect (simulator, SIGNAL(finishedTimeStep ()), graphicsScene, SLOT(updateScene()));
  
  connect (simulator, SIGNAL(logEvent ( const QString & )) , logTextEdit, SLOT (append ( const QString & )));
  
}




/****************************************************************************
**
** Author: Richard Baxter
**
** Default destructor
**
****************************************************************************/

WSNsim::~WSNsim () 
{
  // TODO delete scene?
  delete sensorNetwork;
  delete graphicsView;
  delete graphicsScene;
}



void WSNsim::incrementTimeStep() {
  
    simulator->incrementTimeStep();
}



} /* end of GUI namespace */

} /* end of WSN namespace */
















