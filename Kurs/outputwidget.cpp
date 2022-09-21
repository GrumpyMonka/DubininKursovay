#include "outputwidget.h"
#include "ui_outputwidget.h"
#include "diagramitemcomposite.h"
#include "diagramitemsparql.h"

OutputWidget::OutputWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OutputWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    engine = new QScriptEngine(this);
    network = new MyNetwork(this);
    api = new API(this);

    QScriptValue apiVal = engine->newQObject( api );
        engine->globalObject().setProperty("api", apiVal);
    QScriptValue outputVal = engine->newQObject( ui->textEdit_2 );
        engine->globalObject().setProperty("output", outputVal );
    QScriptValue networkVal = engine->newQObject(network);
        engine->globalObject().setProperty("network", networkVal);
    QScriptValue progress = engine->newQObject( ui ->progressBar );
        engine->globalObject().setProperty("progress", progress);
}

OutputWidget::~OutputWidget()
{
    delete ui;
}

void OutputWidget::setText(QString str){
    ui->textEdit->setText(str);
}

void OutputWidget::Script( QVector<DiagramItem*>& obj ){
    api->block_list = obj;
    QString script = "<p style=\"white-space: pre-wrap;\">";
    for(int i = 0; i < api->block_list.size(); i++){
        script += createScript( i );
        if(  DiagramItemBased::Type == api->block_list[i]->type() && ( ( DiagramItemBased* )( api->block_list[i] ) )->getName() == "END"){
            end_block = i;
        }
    }
    script += "</p>";
    ui->textEdit->setHtml(script);
}

QString OutputWidget::getHtmlLine(QString line, QString style){
    return "<span style=\"margin-top:0px; " + style + "\">" + line + "</span><br>";
}

QString OutputWidget::createScript( int index ){
    QString result = "";
    DiagramItem* diagram_item = api->block_list[index];

    result += getHtmlLine( "\nblocks_list.push( new Block( " );
    result += getHtmlLine( "\tfunction( x ) {" );

    switch ( diagram_item->type() )
    {
        case DiagramItemBased::Type :
            if( ( static_cast<DiagramItemBased*>( diagram_item ) )->GetInputData() != "")
                result += getHtmlLine( "\t\tvar input = " + ( static_cast<DiagramItemBased*>( diagram_item ) )->GetInputData() + ";");
            break;

        case DiagramItemSparql::Type :
            result += getHtmlLine( "\t\tvar input = \"\";");
            break;
    }

    result += getHtmlLine( "\t\tvar y = [];" );

    QStringList list;
    switch ( diagram_item->type() )
    {
        case DiagramItemBased::Type :
            list = ( static_cast<DiagramItemBased*>( diagram_item ) )->getSetting()->script.split( "\n" );
            break;

        case DiagramItemSparql::Type :
            list = ( static_cast<DiagramItemSparql*>( diagram_item ) )->getSetting()->ConvertToBasedBlockSetting()->script.split( "\n" );
            break;
    }

    foreach(QString iter, list){
        for(int  i = 0; i < iter.size(); i++){
            if(iter[i] == "<"){
                iter = iter.mid(0, i) + "&lt;" + iter.mid(i + 1, iter.size());
            }
            if(iter[i] == ">"){
                iter = iter.mid(0, i) + "&gt;" + iter.mid(i + 1, iter.size());
            }
        }
        result += getHtmlLine("\t\t" + iter);
    }

    result += getHtmlLine( "\t\treturn y;" );
    result += getHtmlLine( "\t}," );

    result += getHtmlLine( "\t[ ]," );

    QString temp = "[ ";

    foreach(Arrow* arrow, api->block_list[index]->getArrows()){
        if(arrow->startItem() != api->block_list[index]){
            temp += QString::number( api->block_list.indexOf( arrow->startItem() ) );
            temp += ", ";
        }
    }

    if(temp[temp.size() - 2] == ",")
        temp.remove(temp.size() - 2, 1);

    temp += "]";

    result += getHtmlLine( "\t" + temp );
    result += getHtmlLine( "));\n" );
    return result;
}

QString OutputWidget::loadScript(QString path){
    QFile f(path);
    QScriptValue result;
    if(f.open(QIODevice::ReadOnly)){
        QString str = f.readAll();
        result = engine->evaluate(str, path);
        if(result.isError()){
            return result.toString();
        }
    }else{
        return "Failed load! (" + path + ")";
    }
    return "";
}

void OutputWidget::on_pushButton_clicked()
{
    engine->pushContext();
    ui->textEdit_2->disconnect();
    ui->textEdit_2->clear();
    QScriptValue result;

    if(ui->checkBox_2->isChecked()){
        QString temp = loadScript("Scripts/script.js");
        if(temp.length()){
            ui->textEdit_2->setText("Defult script: " + temp);
        }
    }

    if(ui->checkBox->isChecked()){
        QString temp = loadScript("Scripts/XMLHttpRequest.js");
        if(temp.length()){
            ui->textEdit_2->setText("Defult script: " + temp);
        }
    }
    QString temp = loadScript("Scripts/progress.js");
    if(temp.length()){
        ui->textEdit_2->setText("Progress script: " + temp);
        return;
    }

    result = engine->evaluate(ui->textEdit->toPlainText());
    if(result.isError()){
        ui->textEdit_2->setText( "User script: " + result.toString());
        return;
    }

    //temp = loadScript("C:/Temp/Study/6 semestr/Kurs/Kurs/scripts/block_logic.js");
    temp = loadScript("Scripts/block_logic.js");
    if(temp.length()){
        ui->textEdit_2->setText("Failed script: " + temp);
        return;
    }

    result = engine->evaluate("indexOfEnd = " + QString::number(end_block) + ";");
    if(result.isError()){
        ui->textEdit_2->setText( "Failed run script: " + result.toString());
        return;
    }

    result = engine->evaluate("main('run');");

    if(result.isError()){
        ui->textEdit_2->setText( "Failed run script: " + result.toString());
        return;
    }
    engine->popContext();
}
