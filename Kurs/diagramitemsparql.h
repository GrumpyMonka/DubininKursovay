#ifndef DIAGRAMITEMSPARQL_H
#define DIAGRAMITEMSPARQL_H

#include "diagramitem.h"
#include "sparqlblocksetting.h"
#include "diagramtextitem.h"
#include <QGraphicsProxyWidget>

class DiagramItemSparql : public DiagramItem
{
public:
    enum { Type = UserType + 10 };
    int type() const override { return Type; }

    DiagramItemSparql( QMenu* contextMenu, SparqlBlockSetting* settingf = new SparqlBlockSetting(),
                       QGraphicsItem* parent = nullptr );

    void setSetting( SparqlBlockSetting* settingf );
    QPixmap image() const override;
    QString getName();
    SparqlBlockSetting* getSetting();
    void setDrawPicture( bool );

private:
    DiagramTextItem* name;
    QGraphicsProxyWidget* proxy_picture;
    QLabel* picture;
    SparqlBlockSetting* setting;
};

#endif // DIAGRAMITEMSPARQL_H
