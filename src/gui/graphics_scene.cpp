

#include "graphics_scene.h"

#include <QDebug>


namespace WSN
{

namespace GUI
{

  

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

GraphicsScene::GraphicsScene(const Simulator::SensorNetwork * sensorNetwork, const Simulator::DiscreteSimulator * simulator) : QGraphicsScene(), swebLines(0) , sensorNetwork(sensorNetwork), signalList(simulator->getSignalList()) {
  
  
  this->setItemIndexMethod(QGraphicsScene::NoIndex);
  
  sensorNetworkNodes = QVector<const Simulator::Node::DiscreteSim *>::fromStdVector (sensorNetwork->getConstSimNodePointers());
  setupScene();
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

GraphicsScene::~GraphicsScene() {


}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void GraphicsScene::setupScene() {

  penWidth = 0.1;
  
  this->setBackgroundBrush(QBrush(Qt::black));
  this->setForegroundBrush(QBrush(Qt::white,0));

  Q_FOREACH (const Simulator::Node::DiscreteSim * node, sensorNetworkNodes) {

 // QHash<const Simulator::Node*, QPolygon polygon> polyHash;

    /*QPolygonF poly;

    poly  << QPointF(-drawSize, -drawSize)
          << QPointF(+drawSize, -drawSize)
          << QPointF(+drawSize, +drawSize)
          << QPointF(-drawSize, +drawSize);*/

    QPolygonF backPoly = makeCircle( 32, 1.2 );
    QPolygonF poly = makeCircle( 32, 0.7 );

    poly.translate(node->x(), node->y());
    backPoly.translate(node->x(), node->y());

    polyHash[node] = addPolygon ( poly , QPen(Qt::black, 0), QBrush(Qt::white));
    backPolyHash[node] = addPolygon ( backPoly ,QPen(Qt::black, 0),  QBrush(Qt::white));
    
    polyHash[node]->setZValue ( 1 );
    backPolyHash[node]->setZValue ( 0 );
    
    //nodeHash[polyHash[node]] = node;
    
    //sendingLines[node] = addLine ( 0,0,0,0 , getPen(Qt::yellow) );
    //sendingLines[node]->setVisible(false);
    //sendingLines[node]->setZValue ( 1.5 );
    
    //sendingBlobs[node] = addPolygon(makeCircle(32, 0.5), QPen(Qt::black, 0), QBrush(Qt::darkYellow));
    //sendingBlobs[node]->setVisible(false);
    //sendingBlobs[node]->setZValue ( 1.6 );
  }

  //sendingLines = scene->createItemGroup (QList<QGraphicsItem *> ());
    
  setupSWebLines();
   
  
  updateScene();
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

QPen GraphicsScene::getPen(const QColor& c, qreal width) {
  return QPen(QBrush(c), width == -1?penWidth:width);
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void GraphicsScene::setupSWebLines() {

  if (swebLines)
    this->destroyItemGroup ( swebLines );

  QList<QGraphicsItem *> items;

  qint32 numberOfClustersOut = 8;
  
  qreal currentAngle = 0.0;
  while (currentAngle < 360.0) {
    items.append((QGraphicsItem*)addLine ( QLineF::fromPolar ( numberOfClustersOut*sensorNetwork->getThreshDegree(), currentAngle ), getPen(Qt::green, 0) ));
    currentAngle += sensorNetwork->getScanAngle();
  }

  for (qint32 i = 0 ; i < numberOfClustersOut ; i++) {
    qreal thresh = sensorNetwork->getThreshDegree() * i;

    items.append((QGraphicsItem*)addPolygon ( makeCircle( 64, thresh ), getPen(Qt::green, 0)));
  }

  swebLines = this->createItemGroup (items);
  swebLines->setZValue ( -1 );
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

QPolygonF GraphicsScene::makeCircle(qint32 segments, qreal radius) {

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

void GraphicsScene::updateScene() {

  emit aquireNetworkNodesLock();

  
  Q_FOREACH(const Simulator::Node::DiscreteSim * node, sensorNetworkNodes) {
  
    QGraphicsPolygonItem * polyItem = polyHash[node];
    QGraphicsPolygonItem * backPolyItem = backPolyHash[node];
    
    if (node->type == Simulator::Node::DiscreteSim::Sensor) {
      const Simulator::Node::SensorLayers::Layers* sensor = dynamic_cast<const Simulator::Node::SensorLayers::Layers*>(node);
      if (sensor->grpId % 2 == 0)
        backPolyItem->setBrush(QBrush(Qt::red));
      else
        backPolyItem->setBrush(QBrush(Qt::white));
        
    }
      
    //qDebug() << typeid(node).name();
    
    if (node->type == Simulator::Node::DiscreteSim::Sensor)
      backPolyItem->setVisible(dynamic_cast<const Simulator::Node::SensorLayers::Network*>(node)->isHead());
    else if (node->type == Simulator::Node::DiscreteSim::BaseStation)
      backPolyItem->setVisible(true);
  
    
    
  
    /*QGraphicsLineItem * sendingLine = sendingLines[node];
    sendingLine->setVisible(false);
    QGraphicsPolygonItem * sendingBlob = sendingBlobs[node];
    sendingBlob->setVisible(false);*/
    /* TODO */
    /*switch(node->state()) {
    
      case Simulator::Node::Receiving:
        polyItem->setBrush(QBrush(Qt::red));
        break;
        
      case Simulator::Node::Sending:
        polyItem->setBrush(QBrush(Qt::blue));
        sendingLine->setVisible(true);
        sendingLine->setLine (node->getOtherNode()->x(), node->getOtherNode()->y(),  node->x(), node->y());
        
        sendingBlob->setVisible(true);
        sendingBlob->setPos ( sendingLine->line().pointAt ( node->getPercentageDone() ) );
        break;
      
      case Simulator::Node::Idle:      
        polyItem->setBrush(QBrush(Qt::gray));
      break;
      
      case Simulator::Node::OutOfEnergy:      
        polyItem->setBrush(QBrush(Qt::black));
      break;
      
      case Simulator::Node::ReadyToSend:      
        polyItem->setBrush(QBrush(Qt::green));
      break;
      
    
    
    }*/
    
  }
  for (int index = 0 ;; index++) {
      
    if (index < signalList.size()) { /* index is in range of signals*/
      if (index >= signalLines.size()) { /* index is out of range of lines*/
        /* create more lines */
        //qDebug() << "creating line";
        signalLines.append(addLine ( 0,0,0,0 , getPen(Qt::yellow) ));
      }
      
      QGraphicsLineItem * lineItem = signalLines[index];
    
      const Simulator::Signal& signal = signalList[index];
      lineItem->setLine (signal.src->x(), signal.src->y(), signal.dst->x(), signal.dst->y());
      lineItem->setVisible(true);
    }
    else /* index is out of range of signals*/
      if (index < signalLines.size())/* index is out of range of lines*/
        signalLines[index]->setVisible(false);
      else
        break;
      
    
    //qDebug() << "drew line " << index;
    
  }
  
  emit releaseNetworkNodesLock();
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void GraphicsScene::wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent ) {
  qDebug() << "lol what!";
}









} /* end of GUI namespace */

} /* end of WSN namespace */















