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
  
  std::vector<Simulator::Node const *> snNodes = sensorNetwork->getAllNodes();
  
  
  /* draws all the nodes - TODO move to a more appropriate function*/
  
  double drawSize = 5;
  for (int i = 0 ; i < snNodes.size() ; i++) {
    scene->addLine ( QLineF(
                            +drawSize/2 + snNodes[i]->x, 
                            +drawSize/2 + snNodes[i]->y, 
                            -drawSize/2 + snNodes[i]->x, 
                            -drawSize/2 + snNodes[i]->y) 
                            );
                            
    scene->addLine ( QLineF(
                            +drawSize/2 + snNodes[i]->x, 
                            -drawSize/2 + snNodes[i]->y, 
                            -drawSize/2 + snNodes[i]->x, 
                            +drawSize/2 + snNodes[i]->y) 
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


