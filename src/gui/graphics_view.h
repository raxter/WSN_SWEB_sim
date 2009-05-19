#ifndef __WSN_GRAPHICS_VIEW_H__
#define __WSN_GRAPHICS_VIEW_H__


#include <QGraphicsView>
#include <QWheelEvent>


namespace WSN
{

namespace GUI
{


class GraphicsView : public QGraphicsView {
  Q_OBJECT

  public:
  
  GraphicsView();
  ~GraphicsView();

  void setZoom (qreal newZoom);
  

  protected: /* event handlers */
  
  void wheelEvent ( QWheelEvent * e );
  
  qreal zoom;
  qreal zoomWheelScale;
  qreal maxZoom;
  qreal minZoom;
};


} /* end of GUI namespace */

} /* end of WSN namespace */

#endif /* __WSN_GRAPHICS_SCENE_H__ */

