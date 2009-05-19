#include "wsnsim.h"

#include <typeinfo>

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

WSNsim::WSNsim () : swebLines(0)
{
  setupUi(this);      /* from ui_wsnsim.h: generated from wsnsim.ui */
  
  WSNgraphicsView->setDragMode ( QGraphicsView::ScrollHandDrag );
  scene = new QGraphicsScene( WSNgraphicsView );
  WSNgraphicsView->setScene ( scene );
  
  qreal zoom = 4.0;
  WSNgraphicsView->scale ( zoom, zoom );
  
  sensorNetwork = new Simulator::SensorNetwork(100,100,100); /* FIXME paramaterise these 100's*/
  
  sensorNetworkNodes = QVector<const Simulator::Nodes::DiscreteSim *>::fromStdVector (sensorNetwork->getConstSimNodePointers());

  simulator = new Simulator::DiscreteSimulator(sensorNetwork);

  setupScene();
  
  
  connect (stepButton, SIGNAL(released ()), this, SLOT(incrementTimeStep()));
  connect (simulator, SIGNAL(finishedTimeStep ()), this, SLOT(updateScene()));
  
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
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void WSNsim::setupScene() {

  penWidth = 0.5;
  
  scene->setBackgroundBrush(QBrush(Qt::black));
  scene->setForegroundBrush(QBrush(Qt::white,0));

  Q_FOREACH (const Simulator::Nodes::DiscreteSim * node, sensorNetworkNodes) {

 // QHash<const Simulator::Node*, QPolygon polygon> polyHash;

    /*QPolygonF poly;

    poly  << QPointF(-drawSize, -drawSize)
          << QPointF(+drawSize, -drawSize)
          << QPointF(+drawSize, +drawSize)
          << QPointF(-drawSize, +drawSize);*/

    QPolygonF backPoly = makeCircle( 32, 1.3 );
    QPolygonF poly = makeCircle( 32, 0.5 );

    poly.translate(node->x(), node->y());
    backPoly.translate(node->x(), node->y());

    polyHash[node] = scene->addPolygon ( poly , QPen(), QBrush(Qt::white, Qt::SolidPattern));
    backPolyHash[node] = scene->addPolygon ( backPoly , getPen(Qt::white)/*, Qt::SolidPattern*/);
    //nodeHash[polyHash[node]] = node;

  }

  sendingLines = scene->createItemGroup (QList<QGraphicsItem *> ());
    
  setupSWebLines();
   
  updateScene();
}


QPen WSNsim::getPen(const QColor& c, qreal width) {
  return QPen(QBrush(c), width == -1?penWidth:width);
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
    items.append((QGraphicsItem*)scene->addLine ( QLineF::fromPolar ( numberOfClustersOut*sensorNetwork->threshDegree(), currentAngle ), getPen(Qt::green, 0) ));
    currentAngle += sensorNetwork->scanAngle();
  }

  for (qint32 i = 0 ; i < numberOfClustersOut ; i++) {
    qreal thresh = sensorNetwork->threshDegree() * i;

    items.append((QGraphicsItem*)scene->addPolygon ( makeCircle( 64, thresh ), getPen(Qt::green, 0)));
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


  Q_FOREACH(const Simulator::Nodes::DiscreteSim * node, sensorNetworkNodes) {
  
    QGraphicsPolygonItem * polyItem = polyHash[node];
    QGraphicsPolygonItem * backPolyItem = backPolyHash[node];
    
    if (typeid(node) == typeid(Simulator::Nodes::DiscreteSims::Sensor*))
      backPolyItem->setVisible(((Simulator::Nodes::DiscreteSims::Sensor*)node)->isHead());
    else if (typeid(node) == typeid(Simulator::Nodes::DiscreteSims::BaseStation*))
      backPolyItem->setVisible(true);
  
    
    if (node->state() != Simulator::Node::Idle) {
      polyItem->setPen(getPen(Qt::red));
    }
    else {
      polyItem->setPen(getPen(Qt::white));
    }
    
    if (node->state() == Simulator::Node::Sending) {
      /*TODO this adding is slowing down the simulation big time, rather use a 10 last lines or something*/
      sendingLines->addToGroup((QGraphicsItem*)scene->addLine ( node->x(), node->y(), node->otherNode()->x(), node->otherNode()->y(), getPen(Qt::gray, 0) ) );
    }

  }
  
}


void WSNsim::incrementTimeStep() {
  
  
  //timerItem->setText ( "Timer: " + QString().setNum(simulator->currentTime()) );
  for (int i = 0 ; i < 50 ; i++)
    simulator->incrementTimeStep();
}


} /* end of GUI namespace */

} /* end of WSN namespace */
















