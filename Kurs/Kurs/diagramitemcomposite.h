#ifndef DIAGRAMITEMCOMPOSITE_H
#define DIAGRAMITEMCOMPOSITE_H

#include "diagramitembased.h"
#include "compositeblocksetting.h"

class DiagramItemComposite : public DiagramItem
{
public:
    enum { Type = UserType + 5 };
    int type() const override { return Type; }

    DiagramItemComposite(QMenu *contextMenu, QGraphicsItem* parent = nullptr);

public slots:
    void updatePolygon();

private:
    CompositeBlockSetting setting;
};

#endif // DIAGRAMITEMCOMPOSITE_H
