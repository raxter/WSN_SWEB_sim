

#include "graphics_scene.h"



namespace WSN
{

namespace GUI
{

  

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

GraphicsScene::GraphicsScene(const Simulator::SensorNetwork * sensorNetwork) : QGraphicsScene(), swebLines(0) , sensorNetwork(sensorNetwork) {
  
   packetTypeColours[Simulator::PacketTypes::NoType]        = Qt::gray;
   packetTypeColours[Simulator::PacketTypes::Init]          = Qt::red;
   packetTypeColours[Simulator::PacketTypes::GrpInit]       = Qt::darkRed;
   packetTypeColours[Simulator::PacketTypes::EnergyReq]     = Qt::cyan;
   packetTypeColours[Simulator::PacketTypes::EnergySend]    = Qt::blue;
   packetTypeColours[Simulator::PacketTypes::DataReq]       = Qt::darkGreen;
   packetTypeColours[Simulator::PacketTypes::DataSend]      = Qt::white;
   packetTypeColours[Simulator::PacketTypes::HeadReAlloc]   = Qt::yellow;
   
   sensorNodeNetworkStateColours[Simulator::Node::SensorLayers::Layers::NetworkUninitialised] = Qt::red;
   sensorNodeNetworkStateColours[Simulator::Node::SensorLayers::Layers::InitialisingGroup]    = Qt::yellow;
   sensorNodeNetworkStateColours[Simulator::Node::SensorLayers::Layers::HeadReAlloc]          = Qt::blue;
   sensorNodeNetworkStateColours[Simulator::Node::SensorLayers::Layers::HeadReAllocWait]      = Qt::cyan;
   sensorNodeNetworkStateColours[Simulator::Node::SensorLayers::Layers::Running]              = Qt::green;
   
  
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


void GraphicsScene::setHighlightNodeValue(int highlightNodeValue) {
  this->highlightNodeValue = highlightNodeValue;
}

/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


void GraphicsScene::clearSignals( ) {

  signalSet.clear();
}
void GraphicsScene::incomingSignalList( const QVector<Simulator::Signal>& list) {

  //Q_FOREACH(const Simulator::Signal& signal, list)
  //  qDebug() << signal.src << ":" << signal.dst;
  
  
  Q_FOREACH(const Simulator::Signal& signal, list) {
  
    signalSet[GraphicsSignal(signal)] = true;
  }
}

void GraphicsScene::updateScene(int nothing ) {

  //qDebug() << "updateScene start";
  //emit aquireNetworkNodesLock();

  
  Q_FOREACH(const Simulator::Node::DiscreteSim * node, sensorNetworkNodes) {
  
    QGraphicsPolygonItem * polyItem = polyHash[node];
    QGraphicsPolygonItem * backPolyItem = backPolyHash[node];
    
    if (node->type == Simulator::Node::DiscreteSim::Sensor) {
      const Simulator::Node::SensorLayers::Layers* sensor = dynamic_cast<const Simulator::Node::SensorLayers::Layers*>(node);
      //NetworkUninitialised, InitialisingGroup, HeadReAlloc, HeadReAllocWait, Running
      if (node->id == highlightNodeValue)
        polyItem->setBrush(QBrush(Qt::red));
      else
        polyItem->setBrush(QBrush(Qt::white));
        
      
      backPolyItem->setBrush(QBrush(sensorNodeNetworkStateColours[sensor->currentNetworkState]));
        
    }
      
    //qDebug() << typeid(node).name();
    
    if (node->type == Simulator::Node::DiscreteSim::Sensor)
      backPolyItem->setVisible(dynamic_cast<const Simulator::Node::SensorLayers::Network*>(node)->isHead());
    else if (node->type == Simulator::Node::DiscreteSim::BaseStation)
      backPolyItem->setVisible(true);
  
    
  }
  
  
  QList<GraphicsSignal> signalList = signalSet.keys ();
  for (int index = 0 ;; index++) {
    //qDebug() << index << ":" << signalList.size() << " to draw, " << signalLines.size() << "available";
      
    //if (signalLines.size() > 500)
      //break;
    
    
    if (index < signalList.size()) { //* index is in range of signals
      if (index >= signalLines.size()) { // index is out of range of lines
        // create more lines 
        //qDebug() << "creating line";
        signalLines.append(addLine ( 0,0,0,0 , getPen(Qt::white) ));
        
        //qDebug() << "creating line, size = " << signalLines.size();
        
      }
      
      QGraphicsLineItem * lineItem = signalLines[index];
    
      //qDebug() << index << " out of " << signalList.size();
      GraphicsSignal& signal = signalList[index];
      
      lineItem->setLine (signal.pos[0], signal.pos[1], signal.pos[2], signal.pos[3]);
      //qDebug() << signal.type;
      lineItem->setPen(getPen(packetTypeColours[signal.type]));
      lineItem->setVisible(true);
    }
    else // index is out of range of signals
      if (index < signalLines.size())// index is out of range of lines
        signalLines[index]->setVisible(false);
      else
        break;
      
    
    //qDebug() << "drew line " << index;
    
  }
  
  //qDebug() << "updateScene end";
  //signalList.clear();
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















