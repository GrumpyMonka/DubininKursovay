#include "diagramitemcomposite.h"

DiagramItemComposite::DiagramItemComposite(QMenu *contextMenu, QGraphicsItem* parent)
    : DiagramItem(contextMenu, parent)
{

}

void DiagramItemComposite::updatePolygon(){
    QSize size;
    if(setting.input.size() > setting.output.size()){
        size.setHeight( 30 + setting.input.size() * 20 );
    }else{
        size.setHeight( 30 + setting.output.size() * 20 );
    }
    size.setWidth( 100 );
    myPolygon.clear();
    myPolygon << QPointF( -size.width() / 2, -size.height() / 2)
              << QPointF( size.width() / 2, -size.height() / 2)
              << QPointF( size.width() / 2, size.height() / 2)
              << QPointF( -size.width() / 2, size.height() / 2)
              << QPointF( -size.width() / 2, -size.height() / 2);
    setPolygon(myPolygon);
}
