#include "diagramsparqlatom.h"

DiagramSparqlAtom::DiagramSparqlAtom( QMenu* contextMenu, QPolygonF polygonf, QGraphicsItem* parent)
    : DiagramItem( contextMenu, parent)
{
    setBrush( Qt::white );

    proxy_line_edit = new QGraphicsProxyWidget(this);
    line_edit = new QLineEdit();
    QRect rect(getStartPos().x() + 5, -12,
          getEndPos().x() - getStartPos().x() - 10, 25);
    line_edit->setGeometry(rect);
    line_edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    line_edit->setStyleSheet("QLineEdit {"
                                "border-width: 1px;"
                                "border-style: solid;"
                                "border-color: rgb(255, 255, 255);"
                                "font-size: 12px;"
                                "color: blue;"
                            "}");
    proxy_line_edit->setWidget(line_edit);

    setMyPolygon( polygonf );
}

void DiagramSparqlAtom::setMyPolygon( QPolygonF polygonf )
{
    myPolygon = polygonf;
    setPolygon( myPolygon );
}

QPolygonF DiagramSparqlAtom::getSetting()
{
    return myPolygon;
}

void DiagramSparqlAtom::setText( const QString &str )
{
    line_edit->setText( str );
}

QString DiagramSparqlAtom::getText()
{
    return line_edit->text();
}
