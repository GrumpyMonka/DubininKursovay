#include "diagramitemsparql.h"
#include "QPainter"

DiagramItemSparql::DiagramItemSparql( QMenu *contextMenu, SparqlBlockSetting* settingf, QGraphicsItem* parent)
    : DiagramItem( contextMenu, parent )
{
    setBrush( Qt::green );

    name = new DiagramTextItem( this, false, true );
    name->setPos(getStartPos());

    proxy_picture = new QGraphicsProxyWidget( this );
    picture = new QLabel();
    picture->setGeometry(getEndPos().x() - 32, getStartPos().y() + 2, 30, 30);
    proxy_picture->setWidget(picture);

    setSetting( settingf );
}

void DiagramItemSparql::setSetting( SparqlBlockSetting* settingf )
{
    setting = settingf;
    name->setHtml("<span style=\"font-size: 15px; text-decoration: underline;\">" + setting->name + "</span>");
    picture->setPixmap(setting->image.scaled(30, 30));
}

QPixmap DiagramItemSparql::image() const
{
    //if(setting->type_image == "self"){
        QPixmap pixmap(150, 150);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(QPen(Qt::black, 8));
        painter.translate(75, 75);
        painter.drawPolyline(myPolygon);

        painter.setPen(QPen(Qt::black, 4));
        int index = 150 / setting->name.size() * 0.75;
        painter.setFont(QFont("Consolas", index));
        painter.drawText(-75, -75, 150, 150, Qt::AlignCenter , setting->name);
        return pixmap;
    //}
    return setting->image;
}

QString DiagramItemSparql::getName()
{
    return setting->name;
}

SparqlBlockSetting* DiagramItemSparql::getSetting()
{
    return setting;
}

void DiagramItemSparql::setDrawPicture( bool flag )
{
    picture->setVisible( flag );
}


