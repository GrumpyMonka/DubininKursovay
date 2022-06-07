#include "diagramview.h"
#include "ui_diagramview.h"

DiagramView::DiagramView(DiagramScene* scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagramView)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    gridLayout = ui->gridLayout;
    graphicsView = ui->graphicsView;
    setScene(scene);
    paint();
}

DiagramView::~DiagramView()
{
    delete ui;
}

void DiagramView::paint(){
    QGroupBox* box = new QGroupBox("", this);
    box->setMinimumWidth(width_box + 20);
    box->setFont(font);

    QLabel* label = new QLabel("Pos", box);
    label->setMaximumWidth(width_box);
    label->setMaximumHeight(30);
    label->setFont(font);

    x_spin = new QSpinBox(box);
    x_spin->setMaximumWidth(width_box);
    x_spin->setFont(font);
    x_spin->setMaximum(5000);
    x_spin->setMinimum(0);
    connect(x_spin, SIGNAL(valueChanged(int)),
            this, SLOT(updatePosScene()));

    y_spin = new QSpinBox(box);
    y_spin->setMaximumWidth(width_box);
    y_spin->setFont(font);
    y_spin->setMaximum(5000);
    y_spin->setMinimum(0);
    connect(y_spin, SIGNAL(valueChanged(int)),
            this, SLOT(updatePosScene()));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(x_spin);
    layout->addWidget(y_spin);
    layout->addSpacerItem(new QSpacerItem(0, 2000, QSizePolicy::Maximum, QSizePolicy::Maximum));
    layout->setStretch(10, 10);

    box->setLayout(layout);
    ui->gridLayout->addWidget(box, 0, 1);
}

DiagramScene* DiagramView::scene(){
    return (DiagramScene*)(ui->graphicsView->scene());
}

void DiagramView::setScene(DiagramScene *scene){
    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(itemSelected(DiagramItem*)),
            this, SLOT(updatePosForm(DiagramItem*)));
}

void DiagramView::updatePosForm(DiagramItem* item){
    if( DiagramScene::CheckItemOnDiagramItem( item->type() ) )
    {
        RedactData = true;
        x_spin->setValue(item->pos().x());
        y_spin->setValue(item->pos().y());
        RedactData = false;
    }
}

void DiagramView::updatePosScene(){
    if(!RedactData && ui->graphicsView->scene()->selectedItems().size() &&
            ui->graphicsView->scene()->selectedItems()[0]->type() == DiagramItemBased::Type){
        QGraphicsItem* item = ui->graphicsView->scene()->selectedItems()[0];
        item->setPos(x_spin->value(), y_spin->value());
    }
}
