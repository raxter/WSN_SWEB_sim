

#include "graphics_view.h"

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

GraphicsView::GraphicsView() : QGraphicsView(), zoom(1), maxZoom(50), minZoom(0.1), zoomWheelScale(1.1) {

  setZoom(4.0);

  
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
  setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
  
  
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

GraphicsView::~GraphicsView() {


}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/


void GraphicsView::setZoom (qreal newZoom) {

  if (newZoom < minZoom || newZoom > maxZoom)
    return;

  /* zooms out to normal/unit scale*/
  this->scale ( 1.0/zoom, 1.0/zoom );
  
  zoom = newZoom;
  /* zooms in to new scale*/
  this->scale ( zoom, zoom );
}


/****************************************************************************
**
** Author: Richard Baxter
**
****************************************************************************/

void GraphicsView::wheelEvent ( QWheelEvent * e ) {
  //qDebug() << "lol view what!" << e->delta ();
  
  qreal newZoom = zoom;
  if (e->delta () > 0)
    newZoom*=zoomWheelScale;
  else
    newZoom/=zoomWheelScale;
    
  setZoom(newZoom);
}









} /* end of GUI namespace */

} /* end of WSN namespace */















