#ifndef COMPOSITEBLOCKWINDOW_H
#define COMPOSITEBLOCKWINDOW_H

#include "diagramview.h"
#include "diagramitemcomposite.h"
#include <QSlider>

class CompositeBlockWindow : public DiagramView
{
    Q_OBJECT
public:
    CompositeBlockWindow(DiagramScene*, QWidget* parent = 0);
    void paint() override;

public slots:
    void updateSize();
    void updateSlider();

    void addInput();
    void addOutput();
    void saveBlock();
    void addBlock();
private:
    CompositeBlockSetting setting;
    QVector<DiagramItemBased*> input_list;
    QVector<DiagramItemBased*> output_list;

    DiagramItem* size_item;
    QRectF size = QRectF(-50, -50, 100, 100);
    QSpinBox* size_x_spin;
    QSpinBox* size_y_spin;
    QSlider* size_x_slider;
    QSlider* size_y_slider;
};

#endif // COMPOSITEBLOCKWINDOW_H
