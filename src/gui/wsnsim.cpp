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
  graphicsScene = new GraphicsScene(sensorNetwork);
  
  
  graphicsView->setScene ( graphicsScene );
  
  //animator = new Animator();
  //connect (animator, SIGNAL(tick ()), graphicsScene, SLOT(updateScene()));
  //animator->start();
  
  connect (startButton, SIGNAL(released ( )), simulator, SLOT(startSimulation()));
  connect (stopButton, SIGNAL(released ( )), simulator, SLOT(stopSimulation()));
  
  connect (highlightSpinBox, SIGNAL(valueChanged ( int )), graphicsScene, SLOT(setHighlightNodeValue(int)));
  
  connect (msSpinBox, SIGNAL(valueChanged ( int )), simulator, SLOT(limitedTimeSimulation(int)));
  
  connect (speedSpinBox, SIGNAL(valueChanged ( int )), simulator, SLOT(setSpeed(int)));
  //connect (highlightSpinBox, SIGNAL(valueChanged ( int )), graphicsScene, SLOT(updateScene( int )));
  
  connect (stepButton, SIGNAL(released ()), this, SLOT(incrementTimeStep()));
  //connect (graphicsScene, SIGNAL(aquireNetworkNodesLock()), simulator, SLOT(lock()));
  //connect (graphicsScene, SIGNAL(releaseNetworkNodesLock()), simulator, SLOT(unlock()));
  
  
  connect (simulator, SIGNAL(clearSignals ( )), graphicsScene, SLOT(clearSignals( )),Qt::DirectConnection);
  connect (simulator, SIGNAL(finishedTimeStep ( const QVector<Simulator::Signal>& )), graphicsScene, SLOT(incomingSignalList( const QVector<Simulator::Signal>& )),Qt::DirectConnection);
  
  connect (simulator, SIGNAL(timeUpdated ( int )), currentTimeLabel, SLOT(setNum( int )));
  
  connect (simulator, SIGNAL(tick ( )), graphicsScene, SLOT(updateScene( )));
  connect (simulator, SIGNAL(tick ( )), this, SLOT(recordAndDisplay( )));
  
  connect (simulator, SIGNAL(logEvent ( const QString & )) , logTextEdit, SLOT (append ( const QString & )));
  
  simulator->start();
}




void WSNsim::recordAndDisplay( ) {

  //resultsTextEdit->append( QString::number(simulator->getAverageBatteryLife()));
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
  
  
  simulator->limitedTimeSimulation( msSpinBox->value() );
  //for (int i = 0 ; i < msSpinBox->value() ; i++) /*FIXME, muxt rather pass the number to the simulator so that it'l do the loop in it's thread, not this one (which locks up the gui)*/ {
    
  //  simulator->incrementTimeStep();
    
  //}
    
}



} /* end of GUI namespace */

} /* end of WSN namespace */
















