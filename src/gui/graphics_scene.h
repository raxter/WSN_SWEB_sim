#ifndef __WSN_GRAPHICS_SCENE_H__
#define __WSN_GRAPHICS_SCENE_H__


#include <QHash>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>

#include "simulator/sensor_network.h"

namespace WSN
{

namespace GUI
{


class GraphicsScene : public QGraphicsScene {
  Q_OBJECT

  public: /* class specifc*/

  GraphicsScene(const Simulator::SensorNetwork * sensorNetwork);
  ~GraphicsScene();

  public slots:
  void updateScene();

  private: /* methods */

  /* graphics */
  void setupScene();
  void setupSWebLines();
  QPolygonF makeCircle(qint32 segments, qreal radius);
  QGraphicsSimpleTextItem * timerItem;
  qreal penWidth;
  QPen getPen(const QColor& c, qreal width = -1);

  protected: /* event handlers */

  void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent );


  private:
  const Simulator::SensorNetwork * sensorNetwork;

  /* TODO generalise all these to a class and just have one nodeToGraphicsObjects hash*/
  QVector<const Simulator::Node::DiscreteSim *> sensorNetworkNodes;

  QHash<const Simulator::Node::DiscreteSim *, QGraphicsPolygonItem *>  polyHash;
  QHash<const Simulator::Node::DiscreteSim *, QGraphicsPolygonItem *>  backPolyHash;
  QHash<const Simulator::Node::DiscreteSim *, QGraphicsLineItem *>     sendingLines;
  QHash<const Simulator::Node::DiscreteSim *, QGraphicsPolygonItem *>  sendingBlobs;
  //QHash<QGraphicsPolygonItem *, const Simulator::Node*> nodeHash; /*FIXME do we really need two hashes? - rax*/

  QGraphicsItemGroup * swebLines;

};


} /* end of GUI namespace */

} /* end of WSN namespace */

#endif /* __WSN_GRAPHICS_SCENE_H__ */

