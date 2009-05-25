#ifndef __WSN_GRAPHICS_SCENE_H__
#define __WSN_GRAPHICS_SCENE_H__


#include <QDebug>
#include <QThread>
#include <QHash>
#include <QMap>
#include <QSet>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>

#include "simulator/sensor_network.h"
#include "simulator/discrete_simulator.h" /*just to get Signal struct, FIXME*/

namespace WSN
{

namespace GUI
{


struct GraphicsSignal{
  
  double pos [4];
  long long uniqueId;
  Simulator::PacketTypes::Type type;
  
  GraphicsSignal(const Simulator::Signal& s = Simulator::Signal()) : 
      type(s.type), uniqueId(0)
  {
    int srcId = 0;
    int dstId = 0;
    int totalId = 0;
    int totalTypes = Simulator::PacketTypes::numberOfTypes+2;
    if (s.src) {
      pos[0] = s.src->x();
      pos[1] = s.src->y();
      srcId = s.src->id;
      totalId = s.src->sensorNetwork->numberOfNodes+2;
    }
    if (s.dst) {
      pos[2] = s.dst->x();
      pos[3] = s.dst->y();
      dstId = s.dst->id;
    }
    if (s.src && s.dst) {
      uniqueId = type + srcId*totalTypes + dstId*totalTypes*totalId;
    }
  }
  
  bool operator<(const GraphicsSignal& s) const {
    
    return uniqueId < s.uniqueId;
  }
  
  bool operator==(const GraphicsSignal& s) const {
    
    for (int i = 0 ; i , 4; i ++)
      if (pos[i] != s.pos[i]) return false;
    
    if (type != s.type) return false;
    return true;
  }
  
};

class GraphicsScene : public QGraphicsScene  {
  Q_OBJECT

  public: /* class specifc*/

  GraphicsScene(const Simulator::SensorNetwork * sensorNetwork);
  


  ~GraphicsScene();

  signals:

  //void aquireNetworkNodesLock();
  //void releaseNetworkNodesLock();
  
  public slots:
  void updateScene(int nothing = 0);
  void setHighlightNodeValue(int highlightNodeValue);
  
  void incomingSignalList( const QVector<Simulator::Signal>& list );
  void clearSignals( );

  private: /* methods */

  /* graphics */
  void setupScene();
  void setupSWebLines();
  QPolygonF makeCircle(qint32 segments, qreal radius);
  QGraphicsSimpleTextItem * timerItem;
  qreal penWidth;
  QPen getPen(const QColor& c, qreal width = -1);
  
  bool running;
  void run();

  protected: /* event handlers */
  
  

  void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent );

  public:
  QMap<GraphicsSignal, bool> signalSet;

  private:
  
  int highlightNodeValue;
  
  const Simulator::SensorNetwork * sensorNetwork;

  /* TODO generalise all these to a class and just have one nodeToGraphicsObjects hash*/
  QVector<const Simulator::Node::DiscreteSim *> sensorNetworkNodes;

  QHash<Simulator::PacketTypes::Type, QColor> packetTypeColours;
  QHash<Simulator::Node::SensorLayers::Layers::NetworkState, QColor> sensorNodeNetworkStateColours;

  QHash<const Simulator::Node::DiscreteSim *, QGraphicsPolygonItem *>  polyHash;
  QHash<const Simulator::Node::DiscreteSim *, QGraphicsPolygonItem *>  backPolyHash;
  QVector<QGraphicsLineItem *>      signalLines;
  QVector<QGraphicsPolygonItem *>   signalBlobs;
  //QHash<const Simulator::Node::DiscreteSim *, QGraphicsLineItem *>     sendingLines;
  //QHash<const Simulator::Node::DiscreteSim *, QGraphicsPolygonItem *>  sendingBlobs;
  //QHash<QGraphicsPolygonItem *, const Simulator::Node*> nodeHash; /*FIXME do we really need two hashes? - rax*/

  QGraphicsItemGroup * swebLines;

};


} /* end of GUI namespace */

} /* end of WSN namespace */

#endif /* __WSN_GRAPHICS_SCENE_H__ */

