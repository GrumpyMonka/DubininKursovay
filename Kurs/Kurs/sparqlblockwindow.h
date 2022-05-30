#ifndef SPARQLBLOCKWINDOW_H
#define SPARQLBLOCKWINDOW_H

#include "diagramview.h"
#include "arrow.h"
#include "sparqlblocksetting.h"
#include <QSlider>

class SparqlBlockWindow : public DiagramView
{
    Q_OBJECT
public:
    SparqlBlockWindow(DiagramScene*, QWidget* parent = 0);
    void paint() override;

public slots:
    void updateSize();
    void updateSlider();
    void itemSelected(DiagramItem*);

    void addNewArea();
    void addNewObject();
    void createSparqlBlock();

signals:
    void newSparqlBlockCreated( VirtualSetting* );

private:
    QRectF size = QRectF(-50, -50, 100, 100);
    DiagramItem* selectedItem;
    QSpinBox* size_x_spin;
    QSpinBox* size_y_spin;
    QSlider* size_x_slider;
    QSlider* size_y_slider;
    SparqlBlockSetting* setting;
    QSpinBox* limit_spin;
    QLineEdit* name_line_edit;
};

#endif // SPARQLBLOCKWINDOW_H
