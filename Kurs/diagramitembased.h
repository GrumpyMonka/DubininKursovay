#ifndef DIAGRAMITEMBASED_H
#define DIAGRAMITEMBASED_H

#include "diagramitem.h"
#include "diagramtextitem.h"
#include "basedblocksetting.h"
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QLabel>

class DiagramItemBased : public DiagramItem
{
public:
    enum { Type = UserType + 4 };
    int type() const override { return Type; }

    DiagramItemBased(QMenu *contextMenu, BasedBlockSetting* settingf = new BasedBlockSetting(),
                     QGraphicsItem* parent = nullptr);
    void setSetting(BasedBlockSetting* settingf);
    QPixmap image() const override;
    QString getName();
    BasedBlockSetting* getSetting();
    QString GetInputData();
    void setDrawPicture(bool);

public slots:
    void setInputData(QString);
    void setOutputData(QString);

private:
    DiagramTextItem* name;
    DiagramTextItem* label;
    DiagramTextItem* input_data;
    DiagramTextItem* output_data;
    QLineEdit* line_edit;
    QGraphicsProxyWidget* proxy_line_edit;
    QGraphicsProxyWidget* proxy_picture;
    BasedBlockSetting* setting;
    QLabel* picture;
};

#endif // DIAGRAMITEMBASED_H
