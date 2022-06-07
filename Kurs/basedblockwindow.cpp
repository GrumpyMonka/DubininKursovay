#include "basedblockwindow.h"
#include "ui_basedblockwindow.h"

BasedBlockWindow::BasedBlockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasedBlockWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    setting = new BasedBlockSetting();

    createToolbars();
    setSetting();
}

BasedBlockWindow::~BasedBlockWindow()
{
    delete ui;
}

void BasedBlockWindow::createToolbars(){
    toolbar = addToolBar(tr("File"));
    toolbar->addAction(ui->actionOpen);
    toolbar->addAction(ui->actionSave);
}

QString BasedBlockWindow::getName(QString fileName){
    QStringList lst = fileName.split("/");
    return lst.at(lst.size() - 1);
}

void BasedBlockWindow::on_actionOpen_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Choose File", QDir::currentPath(), tr("JSON (*.json);;All files (*)"));
    QFile file(FileName);
    if (file.open(QIODevice::ReadOnly)){
        ui->statusbar->showMessage("File opened!");
        setting->setSettingFromJson(file.readAll());
        ui->label_4->setText(getName(FileName));
    }else{
        saveSetting();
        ui->statusbar->showMessage("Failed open File", false);
    }
    file.close();
    setSetting();
}

void BasedBlockWindow::on_actionSave_triggered()
{
    saveSetting();
    QString FileName = QFileDialog::getSaveFileName(this, "Save as", QDir::currentPath(), tr("JSON (*.json);;All files (*)"));
    QFile file(FileName);
    if(file.open(QIODevice::WriteOnly)){
        ui->statusbar->showMessage("File saved!");
        QJsonDocument json;
        json.setObject(setting->getJsonFromSetting());
        file.write(json.toJson());
    }else{
        ui->statusbar->showMessage("Failed to save!");
    }
    file.close();
}

void BasedBlockWindow::setSetting(){
    ui->lineEdit_3->setText(setting->name);
    ui->checkBox->setChecked(setting->label);
    ui->checkBox_2->setChecked(setting->line_edit);
    ui->lineEdit->setText(setting->label_text);
    ui->lineEdit_2->setText(setting->line_edit_text);
    ui->textEdit->setText(setting->script);
    if(setting->image.isNull()){
        DiagramItemBased* item = new DiagramItemBased(nullptr, setting);
        setting->image = QPixmap(item->image()).scaled(70, 70);
        delete item;
    }
    ui->label_4->setPixmap(setting->image.scaled(70, 70));
}

void BasedBlockWindow::setSetting(BasedBlockSetting* settingf){
    setting = settingf;
    setSetting();
}

void BasedBlockWindow::on_pushButton_3_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Choose Image", QDir::currentPath(), tr("Image (*.png; *.jpg);;All files (*)"));
    QFile file(FileName);
    if(file.open(QIODevice::ReadOnly)){
        setting->image = QPixmap(FileName);
        setting->image = setting->image.scaled(100, 100);
        ui->statusbar->showMessage("Image open!");
    }else{
        ui->statusbar->showMessage("Failed open image!");
    }
    file.close();
    saveSetting();
    setSetting();
}

void BasedBlockWindow::saveSetting(){
    setting->name = ui->lineEdit_3->text();
    setting->label = ui->checkBox->isChecked();
    setting->line_edit = ui->checkBox_2->isChecked();
    setting->label_text = ui->lineEdit->text();
    setting->line_edit_text = ui->lineEdit_2->text();
    setting->script = ui->textEdit->toPlainText();
    if(rework_item != nullptr){
        rework_item->setSetting(setting);
    }
}

void BasedBlockWindow::on_pushButton_2_clicked()
{
    setting->image = QPixmap();
    saveSetting();
    setSetting();
}

void BasedBlockWindow::on_pushButton_5_clicked()
{
    this->close();
}

void BasedBlockWindow::on_pushButton_6_clicked()
{
    saveSetting();
    if(rework_item == nullptr)
        emit newBasedBlockCreated(setting);
    this->close();
}

void BasedBlockWindow::setBasedBlockOnRework(DiagramItemBased *itemf){
    rework_item = itemf;
    setSetting(rework_item->getSetting());
}
