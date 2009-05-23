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
  simulator = new Simulator::DiscreteSimulator(sensorNetwork);
  graphicsScene = new GraphicsScene(sensorNetwork, simulator);
  
  
  graphicsView->setScene ( graphicsScene );
  
  //animator = new Animator();
  //connect (animator, SIGNAL(tick ()), graphicsScene, SLOT(updateScene()));
  //animator->start();
  
  connect (stepButton, SIGNAL(released ()), this, SLOT(incrementTimeStep()));
  connect (graphicsScene, SIGNAL(aquireNetworkNodesLock()), simulator, SLOT(lock()));
  connect (graphicsScene, SIGNAL(releaseNetworkNodesLock()), simulator, SLOT(unlock()));
  
  connect (simulator, SIGNAL(finishedTimeStep ()), graphicsScene, SLOT(updateScene()));
  
  connect (simulator, SIGNAL(logEvent ( const QString & )) , logTextEdit, SLOT (append ( const QString & )));
  
  simulator->start();
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
  
  simulator->requestStopRunning();
  qDebug() << "waiting for simulator thread to die";
  while (simulator->isRunning ()); /*FIXME, there are better ways to wait for a thread to die ;) */
  delete simulator;
}



void WSNsim::incrementTimeStep() {
  
    simulator->incrementTimeStep();
}



} /* end of GUI namespace */

} /* end of WSN namespace */
















