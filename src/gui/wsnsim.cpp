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

WSNsim::WSNsim () : swebLines(0)
{
  setupUi(this);      /* from ui_wsnsim.h: generated from wsnsim.ui */
  
  WSNgraphicsView->setDragMode ( QGraphicsView::ScrollHandDrag );
  scene = new QGraphicsScene( WSNgraphicsView );
  WSNgraphicsView->setScene ( scene );
  
  qreal zoom = 4.0;
  WSNgraphicsView->scale ( zoom, zoom );
  
  sensorNetwork = new Simulator::SensorNetwork(100,100,100); /* FIXME paramaterise these 100's*/
  simulator = new Simulator::DiscreteSimulator(sensorNetwork);
  setupScene();
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


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void WSNsim::setupScene() {

  QVector<const Simulator::Node *> sensorNetworkNodes = QVector<const Simulator::Node *>::fromStdVector (sensorNetwork->getNodePointers());  

  Q_FOREACH (const Simulator::Node * node, sensorNetworkNodes) {

 // QHash<const Simulator::Node*, QPolygon polygon> polyHash;

    /*QPolygonF poly;

    poly  << QPointF(-drawSize, -drawSize)
          << QPointF(+drawSize, -drawSize)
          << QPointF(+drawSize, +drawSize)
          << QPointF(-drawSize, +drawSize);*/

    QPolygonF poly = makeCircle( 32, 0.5 );

    poly.translate(node->x, node->y);

    polyHash[node] = scene->addPolygon ( poly , QPen(), Qt::SolidPattern);
    nodeHash[polyHash[node]] = node;

  }

    
  setupSWebLines();
   

}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void WSNsim::setupSWebLines() {

  if (swebLines)
    scene->destroyItemGroup ( swebLines );

  QList<QGraphicsItem *> items;

  qint32 numberOfClustersOut = 8;
  
  qreal currentAngle = 0.0;
  while (currentAngle < 360.0) {
    items.append((QGraphicsItem*)scene->addLine ( QLineF::fromPolar ( numberOfClustersOut*sensorNetwork->threshDegree, currentAngle ) ));
    currentAngle += sensorNetwork->scanAngle;
  }

  for (qint32 i = 0 ; i < numberOfClustersOut ; i++) {
    qreal thresh = sensorNetwork->threshDegree * i;

    items.append((QGraphicsItem*)scene->addPolygon ( makeCircle( 64, thresh ) ));
  }


  swebLines = scene->createItemGroup (items);
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

QPolygonF WSNsim::makeCircle(qint32 segments, qreal radius) {

  QPolygonF ret;

  for (qint32 i = 0 ; i < segments ; i++)
    ret << QLineF::fromPolar ( radius, 360.0/segments*i ).p2();

  return ret;
}



/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void WSNsim::updateScene() {

  
  
}


} /* end of GUI namespace */

} /* end of WSN namespace */
















