#include "diagramitembased.h"

DiagramItemBased::DiagramItemBased(QMenu *contextMenu, BasedBlockSetting* settingf, QGraphicsItem* parent)
    : DiagramItem(contextMenu, parent)
{
    setBrush( Qt::white );

    name = new DiagramTextItem(this, false, true);
    label = new DiagramTextItem(this, false, true);
    input_data = new DiagramTextItem(this, false, true);
    output_data = new DiagramTextItem(this, false, true);

    proxy_line_edit = new QGraphicsProxyWidget(this);
    proxy_picture = new QGraphicsProxyWidget(this);

    line_edit = new QLineEdit();
    QRect rect(getStartPos().x() + 4, getEndPos().y() - 30,
               getEndPos().x() - getStartPos().x() - 8, 25);
    line_edit->setGeometry(rect);
    line_edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    line_edit->setStyleSheet("font-size: 12px; color: blue;");

    proxy_line_edit->setWidget(line_edit);

    name->setPos(getStartPos());
    label->setPos(getStartPos().x(), getEndPos().y() - 50);
    input_data->setPos(getStartPos().x(), getStartPos().y() - 25);
    output_data->setPos(getStartPos().x(), getEndPos().y() - 5);


    picture = new QLabel();
    picture->setGeometry(getEndPos().x() - 32, getStartPos().y() + 2, 30, 30);
    proxy_picture->setWidget(picture);

    setSetting(settingf);
}

void DiagramItemBased::setSetting(BasedBlockSetting* settingf){
    setting = settingf;
    name->setHtml("<span style=\"font-size: 15px; text-decoration: underline;\">" + setting->name + "</span>");
    if(setting->label){
        label->setHtml("<span style=\"font-size: 12px;\">" + setting->label_text + "</span>");
    }else{
        label->hide();
    }

    if(setting->line_edit){
        line_edit->setText(setting->line_edit_text);
    }else{
        line_edit->hide();
    }
    picture->setPixmap(setting->image.scaled(30, 30));
}

QPixmap DiagramItemBased::image() const
{
    if(setting->type_image == "self"){
        QPixmap pixmap(150, 150);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(QPen(Qt::black, 8));
        painter.translate(75, 75);
        painter.drawPolyline(myPolygon);

        painter.setPen(QPen(Qt::black, 4));
        int index = 150 / setting->name.size() * 0.75;
        painter.setFont(QFont("Consolas", index));
        painter.drawText(-75, -75, 150, 150, Qt::AlignCenter , setting->name);
        return pixmap;
    }
    return setting->image;
}

QString DiagramItemBased::getName(){
    return setting->name;
}

BasedBlockSetting* DiagramItemBased::getSetting(){
    return setting;
}

QString DiagramItemBased::GetInputData(){
    return line_edit->text();
}

void DiagramItemBased::setDrawPicture(bool flag){
    picture->setVisible(flag);
}

void DiagramItemBased::setInputData(QString vec){
    QString result = "<span style=\"color: green; font-size: 15px;\">";
    result += vec;
    result += "</span>";
    input_data->setHtml(result);
}

void DiagramItemBased::setOutputData(QString vec){
    QString result = "<span style=\"color: red; font-size: 15px\">";
    result += vec;
    result += "</span>";
    output_data->setHtml(result);
}

