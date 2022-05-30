#ifndef SPARQLBLOCKSETTING_H
#define SPARQLBLOCKSETTING_H

#include "virtualsetting.h"
#include "basedblocksetting.h"

#include <QPolygonF>

class SparqlBlockSetting : public VirtualSetting
{
public:
    enum {
        Type = 3
    };

    int type() override { return Type; };
    SparqlBlockSetting();

    struct LineSaver
    {
        int startBlock;
        int endBlock;
        QString text;
    };

    struct BlockSaver
    {
        QString text;
        QPointF pos;
    };

    QVector<BlockSaver> blocks;
    QVector<LineSaver> lines;
    int limit;
    QPixmap image;
    QString name;

    QPolygonF polygon;

    BasedBlockSetting* ConvertToBasedBlockSetting();
};

#endif // SPARQLBLOCKSETTING_H
