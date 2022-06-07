#ifndef BASEDBLOCKSETTING_H
#define BASEDBLOCKSETTING_H

#include "virtualsetting.h"

#include <QString>
#include <QPixmap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QBuffer>
#include <QDebug>

class BasedBlockSetting : public VirtualSetting
{
public:
    enum {
        Type = 1
    };

    int type() override { return Type; }
    BasedBlockSetting();
    void setSettingFromJson(QString str);
    void setSettingFromJson(QJsonValue value);
    QJsonObject getJsonFromSetting();
    QString type_image = "self";
    QString name = "BasicBlock";
    bool label = true;
    QString label_text = "label";
    bool line_edit = true;
    QString  line_edit_text = "";
    QString script = "";
    QPixmap image;
    QJsonValue jsonValFromPixmap(const QPixmap &p);
    QPixmap pixmapFrom(const QJsonValue &val);
};

#endif // BASEDBLOCKSETTING_H
