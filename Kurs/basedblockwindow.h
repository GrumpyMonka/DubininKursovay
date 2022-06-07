#ifndef BASEDBLOCKWINDOW_H
#define BASEDBLOCKWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QToolBar>
#include <QImage>
#include "diagramitembased.h"

namespace Ui {
class BasedBlockWindow;
}

class BasedBlockWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasedBlockWindow(QWidget *parent = nullptr);
    ~BasedBlockWindow();
    QString getName(QString fileName);
    void createToolbars();
    void setSetting();
    void setSetting(BasedBlockSetting*);
    void saveSetting();
    void setBasedBlockOnRework( DiagramItemBased* );

signals:
    void newBasedBlockCreated( VirtualSetting* );

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::BasedBlockWindow *ui;
    DiagramItemBased* rework_item = nullptr;
    BasedBlockSetting* setting;
    QToolBar* toolbar = nullptr;
};

#endif // BASEDBLOCKWINDOW_H
