#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <QtNetwork>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include "diagramitembased.h"

class MyNetwork : public QWidget
{
    Q_OBJECT
public:
    MyNetwork(QWidget *parent = nullptr);

public slots:
    void setUrl(QString str);
    void open(QString type, QString path);
    void setRequestHeader(QString name, QString value);
    void send(QString data = "");
    QString waitAnswer();
    void getResponse(QNetworkReply*);

private:
    QUrl url;

    QString answerflag;
    QString type;
    QString path;
    QNetworkRequest request;
    QVector<QVector<QString>> headers;
    QNetworkAccessManager* manager;
};

#endif // MYNETWORK_H
