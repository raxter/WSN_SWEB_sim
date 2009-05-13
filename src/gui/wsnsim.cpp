#include "wsnsim.h"


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
  
  WSNgraphicsView->setDragMode ( QGraphicsView::ScrollHandDrag );
  scene = new QGraphicsScene( WSNgraphicsView );
  WSNgraphicsView->setScene ( scene );
  
  
  sensorNetwork = new Simulator::SensorNetwork(100,100,100); /* FIXME paramaterise these 100's*/
  
  QVector<const Simulator::Node *> sensorNetworkNodes = QVector<const Simulator::Node *>::fromStdVector (sensorNetwork->getNodePointers());
  
  
  /* draws all the nodes - TODO move to a more appropriate function*/
  
  double drawSize = 5;
  Q_FOREACH (const Simulator::Node * node, sensorNetworkNodes) {
    scene->addLine ( QLineF(
                            +drawSize/2 + node->x, 
                            +drawSize/2 + node->y, 
                            -drawSize/2 + node->x, 
                            -drawSize/2 + node->y) 
                            );
                            
    scene->addLine ( QLineF(
                            +drawSize/2 + node->x, 
                            -drawSize/2 + node->y, 
                            -drawSize/2 + node->x, 
                            +drawSize/2 + node->y) 
                            );
  }
  
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
}




} /* end of GUI namespace */

} /* end of WSN namespace */


