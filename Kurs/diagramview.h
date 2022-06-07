#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QGroupBox>
#include <QSpinBox>
#include <QSpacerItem>
#include "diagramscene.h"

namespace Ui {
class DiagramView;
}

class DiagramView : public QWidget
{
    Q_OBJECT

public:
    explicit DiagramView(DiagramScene*, QWidget *parent = nullptr);
    ~DiagramView();

public slots:
    virtual void paint();
    void setScene( DiagramScene* );
    DiagramScene* scene();
    void updatePosForm(DiagramItem*);
    void updatePosScene();

protected:
    Ui::DiagramView *ui;
    QFont font = QFont("Consolas", 12);
    int width_box = 200;
    bool RedactData = false;
    QGridLayout* gridLayout;
    QGraphicsView* graphicsView;

    QSpinBox* x_spin;
    QSpinBox* y_spin;
};

#endif // DIAGRAMVIEW_H
