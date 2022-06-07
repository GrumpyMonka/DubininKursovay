/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "mainwindow.h"

const int InsertTextButton = 10;

//! [0]
MainWindow::MainWindow()
{
    loadSettings();

    createActions();
    createToolBox();
    createMenus();
    createToolbars();

    //this->setFont(QFont("Consolas", 8));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);

    tabWidget = new QTabWidget(this);
    layout->addWidget(tabWidget);
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->setTabsClosable(true);
    tabWidget->setUsesScrollButtons(true);
    tabWidget->setMovable(true);
    tabWidget->setFont(QFont("Consolas", 12));
    tabWidget->setStyleSheet("QTabBar::tab { height: 25px; width: 175px; }");
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabClose(int)));

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);    
}
//! [0]

void MainWindow::tabClose(int index){
    tabWidget->widget(index)->deleteLater();
    tabWidget->removeTab(index);
}

DiagramScene* MainWindow::createScene(){
    DiagramScene* scene = new DiagramScene(itemMenu, this);
    scene->setVirtualList( &virtual_blocks_list );
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(doubleClick()),
            this, SLOT(scriptItem()));
    connect(scene, SIGNAL(itemInserted(int)),
            this, SLOT(itemInserted(int)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
            this, SLOT(textInserted(QGraphicsTextItem*)));
    //connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
    //        this, SLOT(itemSelected(QGraphicsItem*)));
    return scene;
}

void MainWindow::slotCreateNewProject(){
    DiagramView* window = new DiagramView(createScene(), this);
    tabWidget->addTab(window, "New project");
    tabWidget->setCurrentWidget(window);

    /*
    view = new QGraphicsView(createScene(), tabWidget);
    tabWidget->addTab(view, "New project");
    tabWidget->setCurrentWidget(view);*/
}

void MainWindow::slotOpenProject(){
    QString FileName = QFileDialog::getOpenFileName(this, "Choose File", QDir::currentPath(), tr("JSON (*.json);;All files (*)"));
    QFile file(FileName);
    QJsonDocument json;
    if (file.open(QIODevice::ReadOnly)){
        json = QJsonDocument::fromJson(file.readAll());
    }else{
        return;
    }
    file.close();

    if(json.isObject()){
        QString name = json["name"].toString();
        DiagramView* window = new DiagramView(createScene(), this);
        tabWidget->addTab(window, QFileInfo(FileName).fileName());
        tabWidget->setCurrentWidget(window);

        QString type = json["type"].toString();

        QJsonValue value = json["blocks"];
        QJsonArray array = json["arrows"].toArray();

        QVector<DiagramItemBased*> based_list;
        int size = value["size"].toInt();
        for(int i = 0; i < size; i++){
            BasedBlockSetting* setting = new BasedBlockSetting();

            setting->setSettingFromJson(value[QString::number(i)]["data"]);
            based_list.push_back(new DiagramItemBased(itemMenu, setting));
            based_list.back()->setBrush(getCurrentScene()->itemColor());
            getCurrentScene()->addItem(based_list.back());
            based_list.back()->setPos(value[QString::number(i)]["pos"]["x"].toInt(),
                    value[QString::number(i)]["pos"]["y"].toInt());
            based_list.back()->setZValue(0);
        }

        for(int i = 0; i < array.size(); i++){
            int index_start = array[i].toObject()["start"].toInt();
            int index_end = array[i].toObject()["end"].toInt();
            getCurrentScene()->createArrow(based_list[index_start], based_list[index_end]);
        }
    }
}

void MainWindow::slotSaveProject(){
    QVector<DiagramItemBased*> based_list;
    QVector<Arrow*> arrow_list;
    if(getCurrentScene() == nullptr)
        return;
    foreach (QGraphicsItem * item, getCurrentScene()->items()){
        if(item->type() == DiagramItemBased::Type){
            based_list.push_back( static_cast<DiagramItemBased*>( item ) );
        }else{
            if(item->type() == Arrow::Type){
                arrow_list.push_back( static_cast<Arrow*>( item ) );
            }
        }
    }

    QJsonDocument json;
    QJsonObject obj;

    obj.insert("type", QJsonValue("project"));
    obj.insert("name", QJsonValue("noname"));

    QJsonObject obj_blocks;
    for(int i = 0; i < based_list.size(); i++){
       QJsonObject temp_obj = based_list[i]->getSetting()->getJsonFromSetting();
       QJsonObject pos;
       pos.insert("x", based_list[i]->pos().x());
       pos.insert("y", based_list[i]->pos().y());
       temp_obj.insert("pos", pos);

       obj_blocks.insert(QString::number(i), temp_obj);
    }
    obj_blocks.insert("size", based_list.size());
    obj.insert("blocks", obj_blocks);

    QJsonArray array_arrow;
    for(int i = 0; i < arrow_list.size(); i++){
        QJsonObject temp_obj;
        temp_obj.insert("start", based_list.indexOf( static_cast<DiagramItemBased*>( arrow_list[i]->startItem() ) ) );
        temp_obj.insert("end", based_list.indexOf( static_cast<DiagramItemBased*>( arrow_list[i]->endItem() ) ) );
        array_arrow.push_back(temp_obj);
    }
    obj.insert("arrows", array_arrow);

    json.setObject(obj);

    QString FileName = QFileDialog::getSaveFileName(this, "Save as", QDir::currentPath(), tr("JSON (*.json);;All files (*)"));
    QFile file(FileName);
    if(file.open(QIODevice::WriteOnly)){
        file.write(json.toJson());
    }
    file.close();
}

void MainWindow::loadSettings(){
    QDir dir;
    dir.setPath("Blocks/");
    if(!dir.exists()){
        return;
    }

    dir.setFilter(QDir::Files | QDir::Dirs);
    QFileInfoList list = dir.entryInfoList();
    QVector<QString> files;
    for(int i = 0; i < list.size(); i++){
        if(list[i].fileName() == "." || list[i].fileName() == "..") continue;

        if(list[i].isFile()){
            files.push_back(list[i].absoluteFilePath());
        }else{
            dir.setPath("Blocks/" + list[i].fileName());
            qDebug() << dir.path();
            QFileInfoList lst = dir.entryInfoList();
            for(int j = 0; j < lst.size(); j++){
                if(lst[j].isFile()){
                    files.push_back(lst[j].absoluteFilePath());
                }
            }
        }
    }

    for( int i = 0; i < files.size(); i++ )
    {
        QFile file( files[i] );
        if( file.open(QIODevice::ReadOnly) )
        {
            QString text = file.readAll();
            QJsonDocument json = QJsonDocument::fromJson( text.toUtf8() );

            QString type = json["type"].toString();
            if ( "basic" == type )
            {
                BasedBlockSetting* setting = new BasedBlockSetting();
                setting->setSettingFromJson( text );
                virtual_blocks_list.push_back( setting );
            }
            else if ( "sparql" == type )
            {
                SparqlBlockSetting* setting = new SparqlBlockSetting();
                setting->setSettingFromJson( text );
                virtual_blocks_list.push_back( setting );
            }
        }
        file.close();
    }
}

//! [1]
void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        getCurrentScene()->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        getCurrentScene()->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        getCurrentScene()->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        getCurrentScene()->setBackgroundBrush(QPixmap(":/images/background4.png"));

    getCurrentScene()->update();
    view->update();
}
//! [1]

DiagramScene* MainWindow::getCurrentScene(){
    DiagramView* item = static_cast<DiagramView*>(tabWidget->currentWidget());
    if(item == nullptr){
        return nullptr;
    }
    return static_cast<DiagramScene*>(item->scene());
}

//! [2]
void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button) {
            button->setChecked(false);
        }
    }
    if(getCurrentScene() == nullptr) return;
    getCurrentScene()->setItemType(id);
    getCurrentScene()->setMode(DiagramScene::InsertItem);
}
//! [2]

void MainWindow::slotReworkBlock(){
    if(getCurrentScene() == nullptr) return;
    foreach(QGraphicsItem* item, getCurrentScene()->selectedItems()){
        if( DiagramItemBased::Type == item->type() ){
            BasedBlockWindow* window = new BasedBlockWindow();
            window->setBasedBlockOnRework( static_cast<DiagramItemBased*>( item ) );
            tabWidget->addTab(window, ( static_cast<DiagramItemBased*>( item ) )->getName() );
            tabWidget->setCurrentWidget(window);
        }
        if( DiagramItemComposite::Type == item->type() ){
            /*
            CompositeBlockWindow* window = new CompositeBlockWindow();
            window->setBasedBlockOnRework(qgraphicsitem_cast<DiagramItemBased*>(item));
            tabWidget->addTab(window, qgraphicsitem_cast<DiagramItemBased*>(item)->getName());
            tabWidget->setCurrentWidget(window);
            */
        }
        //if( DiagramItemSparql::Type == item->type() ){
        //    SparqlBlockWindow* window = new SparqlBlockWindow(createScene(), this);
        //    connect(window, SIGNAL( newSparqlBlockCreated( VirtualSetting* ) ),
        //            this, SLOT( slotOnSignalNewBlockCreated( VirtualSetting* ) ) );
        //    tabWidget->addTab(window, "NewSparqlBlock");
        //    tabWidget->setCurrentWidget( window );
        //}
    }
}

//me
void MainWindow::slotCreateBasedBlock(){
    BasedBlockWindow* window = new BasedBlockWindow(this);
    window->setSetting( new  BasedBlockSetting() );
    connect(window, SIGNAL( newBasedBlockCreated( VirtualSetting* ) ),
            this, SLOT( slotOnSignalNewBlockCreated( VirtualSetting* ) ) );
    tabWidget->addTab(window, "NewBasedBlock");
    tabWidget->setCurrentWidget(window);
}

void MainWindow::slotCreateCompositeBlock(){
    CompositeBlockWindow* window = new CompositeBlockWindow(createScene(), this);
    tabWidget->addTab(window, "scene");
    tabWidget->setCurrentWidget(window);
}

void MainWindow::slotCreateSparqlBlock(){
    SparqlBlockWindow* window = new SparqlBlockWindow( createScene(), createScene(), this );
    connect(window, SIGNAL( newSparqlBlockCreated( VirtualSetting* ) ),
            this, SLOT( slotOnSignalNewBlockCreated( VirtualSetting* ) ) );
    tabWidget->addTab(window, "NewSparqlBlock");
    tabWidget->setCurrentWidget(window);
}

void MainWindow::scriptItem(){
    /*foreach (QGraphicsItem *item, scene->selectedItems()){
        if(item->type() == DiagramItem::Type){
            javascripteditor->setSetting(qgraphicsitem_cast<DiagramItem*>(item)->script);
            javascripteditor->show();
        }
    }
*/
}

void MainWindow::runScene(){
    if( nullptr == getCurrentScene() ) return;
    QVector<DiagramItem*> objects;
    foreach( QGraphicsItem* item, getCurrentScene()->items() ){
        if( DiagramScene::CheckItemOnDiagramItem( item->type() ) ){
            objects.push_back( static_cast<DiagramItem*>( item ) );
        }
    }

    OutputWidget* outputwidget = new OutputWidget( this );
    outputwidget->Script( objects );
    tabWidget->addTab( outputwidget, "Script" );
    tabWidget->setCurrentWidget( outputwidget );
}

//! [3]
void MainWindow::deleteItem()
{
    if(getCurrentScene() == nullptr) return;
    foreach (QGraphicsItem *item, getCurrentScene()->selectedItems()) {
        if (item->type() == Arrow::Type) {
            getCurrentScene()->removeItem(item);
            Arrow *arrow = static_cast<Arrow*>( item );
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    foreach (QGraphicsItem *item, getCurrentScene()->selectedItems()) {
         if ( item->type() == DiagramItem::Type )
             ( static_cast<DiagramItem*>( item ) )->removeArrows();
         getCurrentScene()->removeItem(item);
         delete item;
     }
}
//! [3]

//! [4]
void MainWindow::pointerGroupClicked(int)
{
    if(getCurrentScene() == nullptr) return;
    getCurrentScene()->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [4]

//! [5]
void MainWindow::bringToFront()
{
    if(getCurrentScene() == nullptr) return;
    if (getCurrentScene()->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = getCurrentScene()->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == DiagramItemBased::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [5]

//! [6]
void MainWindow::sendToBack()
{
    if(getCurrentScene() == nullptr) return;
    if (getCurrentScene()->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = getCurrentScene()->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [6]

//! [7]
void MainWindow::itemInserted(int index)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    if(getCurrentScene() != nullptr)
        getCurrentScene()->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(index)->setChecked(false);
}
//! [7]

//! [8]
void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    if(getCurrentScene() != nullptr)
        getCurrentScene()->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [8]

//! [9]
void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}
//! [9]

//! [10]
void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}
//! [10]

//! [11]
void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}
//! [11]

//! [12]
void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}
//! [12]

//! [13]
void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}
//! [13]

//! [14]
void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}
//! [14]

//! [15]
void MainWindow::textButtonTriggered()
{
    if(getCurrentScene() != nullptr)
        getCurrentScene()->setTextColor(qvariant_cast<QColor>(textAction->data()));
}
//! [15]

//! [16]
void MainWindow::fillButtonTriggered()
{
    if(getCurrentScene() != nullptr)
        getCurrentScene()->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}
//! [16]

//! [17]
void MainWindow::lineButtonTriggered()
{
    if(getCurrentScene() != nullptr)
        getCurrentScene()->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}
//! [17]

//! [18]
void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    if(getCurrentScene() != nullptr)
        getCurrentScene()->setFont(font);
}
//! [18]

//! [19]
void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem = ( DiagramTextItem* )( item );

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}
//! [19]

//! [20]
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}
//! [20]

void MainWindow::slotOnSignalNewBlockCreated( VirtualSetting* setting ){
    virtual_blocks_list.push_back( setting );
    int index = virtual_blocks_list.size() - 1;
    layout->addWidget( createCellWidget( setting ), index / 3, index % 3 );
}

void MainWindow::setToolBoxItem(){
    int size_list = virtual_blocks_list.size();
    for(int i = 0; i < size_list; i++){
        layout->addWidget( createCellWidget( virtual_blocks_list[i] ) );
    }

    BasedBlockSetting* setting = new BasedBlockSetting();
    setting->name = "";
    while(size_list < 3){
        layout->addWidget( createCellWidget( setting, false ) );
        size_list++;
    }
}

//! [21]
void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    layout = new QGridLayout();

    layout->setRowStretch(10, 10);
    layout->setColumnStretch(2, 10);

    /*
    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);
*/
    /*
    qDebug() << "h: " << layout->horizontalSpacing() << ", w: " << layout->verticalSpacing();
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);

    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
    layout->setColumnStretch(3, 1);
    layout->setMargin(0);

    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);

    qDebug() << "h: " << layout->horizontalSpacing() << ", w: " << layout->verticalSpacing();
*/
    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);
    layout->setSpacing(0);

    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);


//! [22]
    setToolBoxItem();
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("BasicBlock"));
    toolBox->addItem(backgroundWidget, tr("CompositeBlock"));

}
//! [22]

//! [23]
void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(bringToFront()));
//! [23]

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+T"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    //me
    reworkBlockAction = new QAction(QIcon(":/images/repair.png"), tr("Rework Block"));
    reworkBlockAction->setShortcut(tr("Ctrl+A"));
    reworkBlockAction->setStatusTip(tr("Rework Block"));
    connect(reworkBlockAction, SIGNAL(triggered()),
            this, SLOT(slotReworkBlock()));

    createNewProjectAction = new QAction(QIcon(":/images/new.png"), tr("New project"), this);
    createNewProjectAction->setShortcut(tr("Ctrl+N"));
    createNewProjectAction->setStatusTip(tr("Create New Preject"));
    connect(createNewProjectAction, SIGNAL(triggered()),
            this, SLOT(slotCreateNewProject()));

    openProjectAction = new QAction(QIcon(":/images/open.png"), tr("Open"), this);
    openProjectAction->setShortcut(tr("Ctrl+O"));
    openProjectAction->setStatusTip(tr("Open Project"));
    connect(openProjectAction, SIGNAL(triggered()), this, SLOT(slotOpenProject()));

    saveProjectAction = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    saveProjectAction->setShortcut(tr("Ctrl+S"));
    saveProjectAction->setStatusTip(tr("Save Project"));
    connect(saveProjectAction, SIGNAL(triggered()), this, SLOT(slotSaveProject()));

    createBasedBlockAction = new QAction(QIcon(":/images/based.png"), tr("Based"), this);
    createBasedBlockAction->setShortcut(tr("Ctrl+Q"));
    createBasedBlockAction->setStatusTip(tr("New BasedBlock"));
    connect(createBasedBlockAction, SIGNAL(triggered()), this, SLOT(slotCreateBasedBlock()));

    createCompositeBlockAction = new QAction(QIcon(":/images/composite.png"), tr("Composite"), this);
    createCompositeBlockAction->setShortcut(tr("Ctrl+W"));
    createCompositeBlockAction->setStatusTip(tr("New CompositeBlock"));
    connect(createCompositeBlockAction, SIGNAL(triggered()), this, SLOT(slotCreateCompositeBlock()));

    createSparqlBlockAction = new QAction(QIcon(":/images/SPARQL.png"), tr("SPARQL"), this);
    createSparqlBlockAction->setShortcut(tr("Ctrl+L"));
    createSparqlBlockAction->setStatusTip(tr("New SPARQL Block"));
    connect(createSparqlBlockAction, SIGNAL(triggered()), this, SLOT(slotCreateSparqlBlock()));

    runSceneScriptAction = new QAction(QIcon(":/images/execution.png"), tr("Run"), this);
    runSceneScriptAction->setShortcut(tr("Ctrl+R"));
    runSceneScriptAction->setStatusTip(tr("Run"));
    connect(runSceneScriptAction, SIGNAL(triggered()), this, SLOT(runScene()));

    scriptAction = new QAction(QIcon(":/images/script.png"), tr("Script"), this);
    scriptAction->setShortcut(tr("Ctrl+J"));
    scriptAction->setStatusTip(tr("JavaScript code"));
    connect(scriptAction, SIGNAL(triggered()), this, SLOT(scriptItem()));
    //me

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

//! [24]
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(createNewProjectAction);
    fileMenu->addAction(openProjectAction);
    fileMenu->addAction(saveProjectAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);


    newItemMenu = menuBar()->addMenu(tr("&Blocks"));
    newItemMenu->addAction(createBasedBlockAction);
    newItemMenu->addAction(createCompositeBlockAction);
    newItemMenu->addAction(createSparqlBlockAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);
    itemMenu->addSeparator();
    itemMenu->addAction(reworkBlockAction);
    itemMenu->addAction(scriptAction);
    itemMenu->addAction(runSceneScriptAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}
//! [24]

//! [25]
void MainWindow::createToolbars()
{
//! [25]
    editToolBar = addToolBar(tr("Edit"));

    editToolBar->addAction(createNewProjectAction);
    editToolBar->addAction(openProjectAction);
    editToolBar->addAction(saveProjectAction);

    editToolBar->addSeparator();
    editToolBar->addAction(createBasedBlockAction);
    editToolBar->addAction(createCompositeBlockAction);
    editToolBar->addAction(createSparqlBlockAction);

    editToolBar->addSeparator();
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);
    editToolBar->addAction(reworkBlockAction);
    editToolBar->addAction(scriptAction);
    editToolBar->addAction(runSceneScriptAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

//! [26]
    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));
//! [26]

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
//! [27]
}
//! [27]

//! [28]
QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
//! [28]

//! [29]
QWidget *MainWindow::createCellWidget( VirtualSetting* settingf, bool addButtonGroup )
{
    QIcon icon;
    QString name;
    if ( BasedBlockSetting::Type == settingf->type() )
    {
        BasedBlockSetting* setting = ( BasedBlockSetting* )( settingf );
        name = setting->name;
        icon = QIcon( setting->image.scaled( 50, 50 ) );
    }
    else if ( CompositeBlockSetting::Type == settingf->type() )
    {

    }
    else if ( SparqlBlockSetting::Type == settingf->type() )
    {
        SparqlBlockSetting* setting = ( SparqlBlockSetting* )( settingf );
        name = setting->name;
        QPixmap pixmap( ":/images/sparqlicon.jpg" );
        icon = QIcon( pixmap.scaled( 50, 50 ) );
    }

    QToolButton *button = new QToolButton;
    button->setIcon( icon );
    button->setIconSize( QSize(50, 50) );
    button->setCheckable( true );
    if( addButtonGroup )
        buttonGroup->addButton( button, buttonGroup->buttons().size() );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( button, 0, 0, Qt::AlignHCenter );
    layout->addWidget( new QLabel( name ), 1, 0, Qt::AlignCenter );

    QWidget *widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}
//! [29]

//! [30]
QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
//! [30]

//! [31]
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}
//! [31]

//! [32]
QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
//! [32]
