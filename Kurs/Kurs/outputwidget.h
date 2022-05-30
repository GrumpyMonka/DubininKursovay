#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QMainWindow>
#include "arrow.h"
#include "mynetwork.h"
#include "api.h"
#include "diagramitembased.h"
#include <QScriptEngine>
#include <QScriptValue>

namespace Ui {
class OutputWidget;
}

class OutputWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit OutputWidget(QWidget *parent = nullptr);
    ~OutputWidget();

public slots:
    void setText(QString);
    void Script( QVector<DiagramItem*>& );
    QString createScript(int);
    QString loadScript(QString);
    QString getHtmlLine(QString line, QString style = "");

private slots:
    void on_pushButton_clicked();

private:
    Ui::OutputWidget *ui;
    MyNetwork* network;
    API* api;
    QScriptEngine* engine;
    int end_block = -1;
};

#endif // OUTPUTWIDGET_H
