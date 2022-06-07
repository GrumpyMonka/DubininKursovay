#ifndef API_H
#define API_H

#include <QObject>
#include "diagramitembased.h"

class API : public QObject
{
    Q_OBJECT
public:

    explicit API(QObject* parent = nullptr);

    QVector<DiagramItem*> block_list; // костыль

signals:
    void newStep();

public slots:
    void setInputData(int, QString); // костыль
    void setOutputData(int, QString); // костыль
};

#endif // API_H
