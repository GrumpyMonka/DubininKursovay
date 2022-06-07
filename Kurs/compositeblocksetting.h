#ifndef COMPOSITEBLOCKSETTING_H
#define COMPOSITEBLOCKSETTING_H

#include "basedblocksetting.h"
#include "virtualsetting.h"
#include <QMap>

class CompositeBlockSetting : public VirtualSetting
{
public:
    enum {
        Type = 2
    };

    int type() override { return Type; };
    CompositeBlockSetting();

    void setSettingFromJson(QString str);
    void setSettingFromJson(QJsonValue value);
    QJsonObject getJsonFromSetting();
    BasedBlockSetting setting;
    QVector<BasedBlockSetting> input;
    QVector<BasedBlockSetting> output;
    QMap<BasedBlockSetting, QPointF> based_block_list;
};

#endif // COMPOSITEBLOCKSETTING_H
