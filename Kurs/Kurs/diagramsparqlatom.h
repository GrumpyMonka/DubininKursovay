#ifndef DIAGRAMSPARQLATOM_H
#define DIAGRAMSPARQLATOM_H

#include "diagramitem.h"

class DiagramSparqlAtom : public DiagramItem
{
public:
    enum { Type = UserType + 6 };
    int type() const override { return Type; }

    DiagramSparqlAtom( QMenu* contextMenu, QPolygonF polygonf = QPolygonF(),
                      QGraphicsItem* parent = nullptr );

    void setMyPolygon( QPolygonF polygonf );
    QPolygonF getSetting();
    QString getText();

private:
    QLineEdit* line_edit;
    QGraphicsProxyWidget* proxy_line_edit;
};

#endif // DIAGRAMSPARQLATOM_H
