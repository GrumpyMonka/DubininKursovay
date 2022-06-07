#include "compositeblockwindow.h"

CompositeBlockWindow::CompositeBlockWindow(DiagramScene* scene, QWidget* parent)
    : DiagramView(scene, parent)
{
    size_item = new DiagramItem(scene->getMenu());
    size_item->setPos(2500, 2500);
    scene->addItem(size_item);
    paint();
}

void CompositeBlockWindow::paint(){
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

    QLabel* size_label = new QLabel("Size", box);
    size_label->setMaximumWidth(width_box);
    size_label->setMaximumHeight(30);
    size_label->setFont(font);

    size_x_spin = new QSpinBox(box);
    size_x_spin->setMaximum(width_box);
    size_x_spin->setFont(font);
    size_x_spin->setMaximum(5000);
    size_x_spin->setMinimum(10);
    size_x_spin->setSingleStep(2);
    size_x_spin->setValue(size.width());
    connect(size_x_spin, SIGNAL(valueChanged(int)),
            this, SLOT(updateSize()));

    size_x_slider = new QSlider(Qt::Horizontal, box);
    size_x_slider->setMaximum(5000);
    size_x_slider->setMinimum(0);
    size_x_slider->setValue(size.width());
    size_x_slider->setSingleStep(2);
    size_x_slider->setFont(font);
    connect(size_x_slider, SIGNAL(valueChanged(int)),
            this, SLOT(updateSlider()));

    size_y_spin = new QSpinBox(box);
    size_y_spin->setMaximum(width_box);
    size_y_spin->setFont(font);
    size_y_spin->setMaximum(5000);
    size_y_spin->setMinimum(10);
    size_y_spin->setSingleStep(2);
    size_y_spin->setValue(size.height());
    connect(size_y_spin, SIGNAL(valueChanged(int)),
            this, SLOT(updateSize()));

    size_y_slider = new QSlider(Qt::Horizontal, box);
    size_y_slider->setMaximum(5000);
    size_y_slider->setMinimum(0);
    size_y_slider->setValue(size.height());
    size_y_slider->setSingleStep(2);
    size_y_slider->setFont(font);
    connect(size_y_slider, SIGNAL(valueChanged(int)),
            this, SLOT(updateSlider()));

    QPushButton* button_input = new QPushButton("Add Input");
    button_input->setMaximumWidth(width_box);
    connect(button_input, SIGNAL(clicked()),
            this, SLOT(addInput()));

    QPushButton* button_output = new QPushButton("Add Output");
    button_output->setMaximumWidth(width_box);
    connect(button_output, SIGNAL(clicked()),
            this, SLOT(addOutput()));

    QPushButton* button_save = new QPushButton("Save");
    button_output->setMaximumWidth(width_box);
    connect(button_output, SIGNAL(clicked()),
            this, SLOT(saveBlock()));

    QPushButton* button_add = new QPushButton("Add");
    button_output->setMaximumWidth(width_box);
    connect(button_output, SIGNAL(clicked()),
            this, SLOT(addBlock()));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(x_spin);
    layout->addWidget(y_spin);
    layout->addWidget(size_label);
    layout->addWidget(size_x_spin);
    layout->addWidget(size_x_slider);
    layout->addWidget(size_y_spin);
    layout->addWidget(size_y_slider);
    layout->addWidget(button_input);
    layout->addWidget(button_output);
    layout->addSpacerItem(new QSpacerItem(0, 2000, QSizePolicy::Maximum, QSizePolicy::Maximum));
    layout->addWidget(button_save);
    layout->addWidget(button_add);
    layout->setStretch(10, 10);

    box->setLayout(layout);
    gridLayout->addWidget(box, 0, 1);
}

void CompositeBlockWindow::updateSlider(){
    size_x_spin->setValue(size_x_slider->value());
    size_y_spin->setValue(size_y_slider->value());
    updateSize();
}

void CompositeBlockWindow::updateSize(){
    size_x_slider->setValue(size_x_spin->value());
    size_y_slider->setValue(size_y_spin->value());
    size.setX(-size_x_spin->value() / 2);
    size.setY(-size_y_spin->value() / 2);
    size.setWidth(size_x_spin->value());
    size.setHeight(size_y_spin->value());
    //qDebug() << size;
    QPolygonF polygon;
    polygon << QPointF(size.x(), size.y())
            << QPointF(size.x() + size.width(), size.y())
            << QPointF(size.x() + size.width(), size.y() + size.height())
            << QPointF(size.x(), size.y() + size.height())
            << QPointF(size.x(), size.y());
    size_item->setPolygon(polygon);

    qreal step = size.height() / (input_list.size() + 1);
    for(int i = 0; i < input_list.size(); i++){
        input_list[i]->setPos(size_item->pos().x() + size.x(),
            size_item->pos().y() + size.y() + step * (i + 1));

    }

    step = size.height() / (output_list.size() + 1);
    for(int i = 0; i < output_list.size(); i++){
        output_list[i]->setPos(size_item->pos().x() + size.width() + size.x(),
            size_item->pos().y() + size.y() + step * (i + 1));

    }
}

void CompositeBlockWindow::addInput(){
    BasedBlockSetting* set;
    set->label = false;
    set->line_edit = false;
    set->name = "";

    input_list.push_back(new DiagramItemBased(scene()->getMenu(), set));
    input_list.back()->setBrush(QBrush(QColor(Qt::black)));
    input_list.back()->setPos(2500,2500);
    input_list.back()->setDrawPicture(false);
    input_list.back()->myPolygon.clear();
    input_list.back()->myPolygon << QPointF(-10, -8) << QPointF(10, -8)
                                << QPointF(10, 2) << QPointF(-10, 2)
                                << QPointF(-10, -7);
    input_list.back()->setFlag(QGraphicsItem::ItemIsMovable, false);
    input_list.back()->setPolygon(input_list.back()->myPolygon);
    scene()->addItem(input_list.back());
    updateSize();
}

void CompositeBlockWindow::addOutput(){
    BasedBlockSetting* set;
    set->label = false;
    set->line_edit = false;
    set->name = "";

    output_list.push_back(new DiagramItemBased(scene()->getMenu(), set));
    output_list.back()->setBrush(QBrush(QColor(Qt::black)));
    output_list.back()->setPos(2500,2500);
    output_list.back()->setDrawPicture(false);
    output_list.back()->myPolygon.clear();
    output_list.back()->myPolygon << QPointF(-10, -8) << QPointF(10, -8)
                                << QPointF(10, 2) << QPointF(-10, 2)
                                << QPointF(-10, -7);
    output_list.back()->setFlag(QGraphicsItem::ItemIsMovable, false);
    output_list.back()->setPolygon(output_list.back()->myPolygon);
    scene()->addItem(output_list.back());
    updateSize();
}

void CompositeBlockWindow::saveBlock(){
    // сохранение в json файл
}

void CompositeBlockWindow::addBlock(){
    // скидывание в CompositeBlockSetting И скидывание сигналом в mainwindow
}
