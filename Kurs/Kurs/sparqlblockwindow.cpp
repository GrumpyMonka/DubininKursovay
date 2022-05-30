#include "sparqlblockwindow.h"
#include "diagramsparqlatom.h"

SparqlBlockWindow::SparqlBlockWindow(DiagramScene* scene, QWidget* parent)
    : DiagramView(scene, parent)
{
    paint();
    setting = new SparqlBlockSetting();
    addNewArea();
    connect(scene, SIGNAL(itemSelected(DiagramItem*)),
            this, SLOT(itemSelected(DiagramItem*)));
}

void SparqlBlockWindow::paint(){
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
    size_x_spin->setValue(100);
    connect(size_x_spin, SIGNAL(valueChanged(int)),
            this, SLOT(updateSize()));

    size_x_slider = new QSlider(Qt::Horizontal, box);
    size_x_slider->setMaximum(5000);
    size_x_slider->setMinimum(0);
    size_x_slider->setValue(100);
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
    size_y_spin->setValue(100);
    connect(size_y_spin, SIGNAL(valueChanged(int)),
            this, SLOT(updateSize()));

    size_y_slider = new QSlider(Qt::Horizontal, box);
    size_y_slider->setMaximum(5000);
    size_y_slider->setMinimum(0);
    size_y_slider->setValue(100);
    size_y_slider->setSingleStep(2);
    size_y_slider->setFont(font);
    connect(size_y_slider, SIGNAL(valueChanged(int)),
            this, SLOT(updateSlider()));

    QLabel* name_label = new QLabel( "Name block: ");

    name_line_edit = new QLineEdit();
    name_line_edit->setText( "SPARQL request" );

    QLabel* limit_label = new QLabel( "Limit SPARQL records: " );

    limit_spin = new QSpinBox();
    limit_spin->setMinimum( 0 );
    limit_spin->setMaximum( 1000 );
    limit_spin->setValue( 20 );

    QPushButton* button_new_area = new QPushButton("Add New Area");
    button_new_area->setMaximumWidth(width_box);
    connect(button_new_area, SIGNAL(clicked()),
            this, SLOT(addNewArea()));

    QPushButton* button_new_object = new QPushButton("Add New Object");
    button_new_object->setMaximumWidth(width_box);
    connect(button_new_object, SIGNAL(clicked()),
            this, SLOT(addNewObject()));

    QPushButton* button_save = new QPushButton("Save");
    button_save->setMaximumWidth(width_box);
    connect(button_save, SIGNAL(clicked()),
            this, SLOT(createSparqlBlock()));

    QPushButton* button_add = new QPushButton("Add");
    button_add->setMaximumWidth(width_box);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(x_spin);
    layout->addWidget(y_spin);
    layout->addWidget(size_label);
    layout->addWidget(size_x_spin);
    layout->addWidget(size_x_slider);
    layout->addWidget(size_y_spin);
    layout->addWidget(size_y_slider);
    layout->addWidget( name_label );
    layout->addWidget( name_line_edit );
    layout->addWidget( limit_label );
    layout->addWidget( limit_spin );
    layout->addWidget( button_new_area );
    layout->addWidget( button_new_object );
    layout->addSpacerItem(new QSpacerItem(0, 2000, QSizePolicy::Maximum, QSizePolicy::Maximum));
    layout->addWidget(button_save);
    layout->addWidget(button_add);
    layout->setStretch(10, 10);

    box->setLayout(layout);
    gridLayout->addWidget(box, 0, 1);
}

void SparqlBlockWindow::updateSlider(){
    if(RedactData) return;
    size_x_spin->setValue(size_x_slider->value());
    size_y_spin->setValue(size_y_slider->value());
    updateSize();
}

void SparqlBlockWindow::updateSize(){
    if(RedactData) return;
    size_x_slider->setValue(size_x_spin->value());
    size_y_slider->setValue(size_y_spin->value());
    size.setX(size_x_spin->value() / size.width());
    size.setY(-size_y_spin->value() / size.height());
    size.setWidth(size_x_spin->value());
    size.setHeight(size_y_spin->value());

    try{
        for( auto& point : selectedItem->myPolygon ){
            point.setX( point.x() * size.x() );
            point.setY( point.y() * size.y() );
        }
        selectedItem->setPolygon(selectedItem->myPolygon);
    }catch(...){

    }
}

void SparqlBlockWindow::itemSelected(DiagramItem* item){
    if( DiagramScene::CheckItemOnDiagramItem( item->type() ) )
    {
        selectedItem = item;
        RedactData = true;
        size_x_spin->setValue(item->getEndPos().x() - item->getStartPos().x());
        size_y_spin->setValue(item->getEndPos().y() - item->getStartPos().y());
        size_x_slider->setValue(size_x_spin->value());
        size_y_slider->setValue(size_y_spin->value());
        size.setWidth(size_x_spin->value());
        size.setHeight(size_y_spin->value());
        RedactData = false;
    }
}

void SparqlBlockWindow::addNewArea(){
    DiagramItem* item = new DiagramItem(scene()->getMenu());
    item->setPos(2500, 2500);
    scene()->addItem(item);
    selectedItem = item;
}

void SparqlBlockWindow::addNewObject(){
    DiagramSparqlAtom* dItem = new DiagramSparqlAtom( scene()->getMenu(), setting->polygon );
    dItem->setPos(2500, 2500);
    scene()->addItem(dItem);

}

void SparqlBlockWindow::createSparqlBlock()
{
    SparqlBlockSetting* setting = new SparqlBlockSetting();
    QVector<DiagramSparqlAtom*> blocks;
    QVector<Arrow*> arrows;
    for( QGraphicsItem* item : scene()->items() )
    {
        if(  Arrow::Type == item->type() )
        {
            Arrow* arrow = qgraphicsitem_cast<Arrow*>( item );
            arrows.push_back( arrow );
        }
        else if ( DiagramSparqlAtom::Type == item->type() )
        {
            DiagramSparqlAtom* based = qgraphicsitem_cast<DiagramSparqlAtom*>( item );
            blocks.push_back( based );
        }
    }

    for ( auto& block : blocks )
    {
        setting->blocks.push_back( { block->getText(), block->pos() } );
    }

    for ( auto& arrow : arrows )
    {
        setting->lines.push_back( { blocks.indexOf( qgraphicsitem_cast<DiagramSparqlAtom*>( arrow->startItem() ) ),
                                    blocks.indexOf( qgraphicsitem_cast<DiagramSparqlAtom*>( arrow->endItem() ) ),
                                    arrow->getText() } );
    }

    setting->name = name_line_edit->text();
    setting->limit = limit_spin->value();

    emit newSparqlBlockCreated( setting );
}
