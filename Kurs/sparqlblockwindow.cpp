#include "sparqlblockwindow.h"
#include "diagramsparqlatom.h"

#include <QFileDialog>

SparqlBlockWindow::SparqlBlockWindow( DiagramScene* scene, QWidget* parent )
    : DiagramView( scene, parent )
{
    paint();
    setting = new SparqlBlockSetting();
    setNewScene();
    connect( scene, SIGNAL( itemSelected( DiagramItem* ) ),
            this, SLOT( itemSelected( DiagramItem* ) ) );
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
    name_line_edit->setText( "SPARQL" );

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

    QPushButton* button_open = new QPushButton( "Open" );
    button_open->setMaximumWidth( width_box );
    connect( button_open, SIGNAL( clicked() ),
            this, SLOT( openFile() ) );

    QPushButton* button_save = new QPushButton("Save");
    button_save->setMaximumWidth(width_box);
    connect(button_save, SIGNAL(clicked()),
            this, SLOT(createSparqlBlock()));

    QPushButton* button_add = new QPushButton("Add");
    button_add->setMaximumWidth(width_box);
    connect( button_add, SIGNAL( clicked() ),
            this, SLOT( createBlock() ) );

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
    layout->addWidget( button_open );
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
    QPolygonF polygon;
    polygon << QPointF( -300, 200 )
            << QPointF( 300, 200 )
            << QPointF( 300, -200 )
            << QPointF( -300, -200 )
            << QPointF( -300, 200 );
    item->myPolygon = polygon;
    item->setPolygon( item->myPolygon );
    item->setPos(2500, 2500);
    scene()->createArrow( Areas[0], item )->setZValue( -2000 );
    scene()->addItem(item);
    selectedItem = item;
}

void SparqlBlockWindow::addNewObject(){
    DiagramSparqlAtom* dItem = new DiagramSparqlAtom( scene()->getMenu(), setting->polygon );
    dItem->setPos(2500, 2500);
    scene()->addItem(dItem);
    selectedItem = dItem;
}

void SparqlBlockWindow::createSparqlBlock()
{
    SparqlBlockSetting* setting = getSetting();

    QString FileName = QFileDialog::getSaveFileName( this, "Save as", QDir::currentPath(), tr( "JSON (*.json);;All files (*)" ) );
    QFile file( FileName );
    if( file.open(QIODevice::WriteOnly ) ){
        QJsonDocument json;
        json.setObject( setting->getJsonFromSetting() );
        file.write( json.toJson() );
    }
    file.close();

    emit newSparqlBlockCreated( setting );
}

void SparqlBlockWindow::openFile()
{
    QString FileName = QFileDialog::getOpenFileName( this, "Choose File", QDir::currentPath(), tr( "JSON (*.json);;All files (*)" ) );
    QFile file( FileName );
    if ( file.open( QIODevice::ReadOnly ) ){
        setting->setSettingFromJson( file.readAll() );
    }
    file.close();
    setSetting();
}

void SparqlBlockWindow::setSetting()
{
    name_line_edit->setText( setting->name );
    limit_spin->setValue( setting->limit );
    scene()->clear();
    setNewScene();
    /*
    QVector<DiagramSparqlAtom*> item_list;
    for( const auto& next_block : setting->blocks )
    {
        DiagramSparqlAtom* item = new DiagramSparqlAtom( scene()->getMenu(), setting->polygon );
        item->setPos( next_block.pos );
        item->setText( next_block.text );
        item_list.push_back( item );
        scene()->addItem( item );
    }

    for( const auto& next_line : setting->lines )
    {
        scene()->createArrow( item_list[next_line.startBlock], item_list[next_line.endBlock] )->setText( next_line.text );
    }
    */
}

void SparqlBlockWindow::createBlock()
{
    emit newSparqlBlockCreated( getSetting() );
}

void SparqlBlockWindow::setNewScene()
{
    scene()->clear();
    QPolygonF polygon;
    polygon << QPointF( -300, 200 )
            << QPointF( 300, 200 )
            << QPointF( 300, -200 )
            << QPointF( -300, -200 )
            << QPointF( -300, 200 );

    DiagramItem* itemOrigin = new DiagramItem( scene()->getMenu() );
    itemOrigin->myPolygon = polygon;
    itemOrigin->setPolygon( itemOrigin->myPolygon );
    itemOrigin->setPos( 2150, 2250 );
    itemOrigin->setBrush( Qt::white );
    itemOrigin->setZValue( -2000 );

    DiagramItem* itemMinus = new DiagramItem( scene()->getMenu() );
    itemMinus->myPolygon = polygon;
    itemMinus->setPolygon( itemMinus->myPolygon );
    itemMinus->setPos( 2850, 2250 );
    itemMinus->setBrush( Qt::white );
    itemMinus->setZValue( -2000 );

    DiagramItem* itemUnion = new DiagramItem( scene()->getMenu() );
    itemUnion->myPolygon = polygon;
    itemUnion->setPolygon( itemUnion->myPolygon );
    itemUnion->setPos( 2150, 2750 );
    itemUnion->setBrush( Qt::white );
    itemUnion->setZValue( -2000 );

    scene()->addItem( itemOrigin );
    scene()->addItem( itemMinus );
    scene()->addItem( itemUnion );
    Areas.push_back( itemOrigin );
    Areas.push_back( itemMinus );
    Areas.push_back( itemUnion );

    Arrow* arrow_OM = scene()->createArrow( itemOrigin, itemMinus );
    arrow_OM->setText( "MINUS" );
    arrow_OM->setZValue( -3000 );

    Arrow* arrow_OU = scene()->createArrow( itemOrigin, itemUnion );
    arrow_OU->setText( "UNION" );
    arrow_OU->setZValue( -3000 );
}

SparqlBlockSetting* SparqlBlockWindow::getSetting()
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
        QString path;
        for( const auto& item : Areas )
        {
            if ( CheckCollisionArea( block, item ) )
            {
                if ( item->getArrows().size() )
                {
                    Arrow* arrow = item->getArrows()[0];
                    if ( arrow->endItem() == item )
                    {
                        path = arrow->getText();
                    }
                    else
                    {
                        path = "ORIGIN";
                    }
                }
                setting->blocks.push_back( { block->getText(), block->pos(), path } );
            }
        }
    }

    for ( auto& arrow : arrows )
    {
        int p1 = blocks.indexOf( qgraphicsitem_cast<DiagramSparqlAtom*>( arrow->startItem() ) );
        int p2 = blocks.indexOf( qgraphicsitem_cast<DiagramSparqlAtom*>( arrow->endItem() ) );
        if( -1 != p1 && -1 != p2 )
        {
            setting->lines.push_back( { p1, p2, arrow->getText() } );
        }
    }

    for ( const auto& area : Areas )
    {
        QString path;
        Arrow* arrow = area->getArrows()[0];
        if ( arrow->endItem() == area )
        {
            path = arrow->getText();
        }
        else
        {
            path = "ORIGIN";
        }
        setting->areas.push_back( { QPointF( area->getEndPos().x() - area->getStartPos().x(),
                                 area->getEndPos().y() - area->getStartPos().y() ), area->pos(), path } );
    }

    setting->name = name_line_edit->text();
    setting->limit = limit_spin->value();
    return setting;
}

bool SparqlBlockWindow::CheckCollisionArea( const DiagramItem* item, DiagramItem* area )
{
    QPointF item_pos = item->pos();
    if ( item_pos.x() > area->pos().x() + area->getStartPos().x() &&
         item_pos.x() < area->pos().x() + area->getEndPos().x() &&
         item_pos.y() > area->pos().y() + area->getStartPos().y() &&
         item_pos.y() < area->pos().y() + area->getEndPos().y() )
    {
        return true;
    }
    return false;
}

