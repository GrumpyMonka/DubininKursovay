#include "outputwidget.h"
#include "ui_outputwidget.h"

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

/*
QString OutputWidget::createScript(int index){
    QString result;
    QString script;
    script = "<p style=\"white-space: pre-wrap;\">" + getHtmlLine("<span style=\"color: #569cd6\">function</span> func_" + QString::number(index) + "(){") +
            getHtmlLine("\tvar x = [];") +
            getHtmlLine("\tvar y = [];");

    int temp_index = index;
    foreach(Arrow * arrow, item->getArrows()){
        if(arrow->startItem() != item){
            script += getHtmlLine("\tx.push(<span style=\"color: red\";>func_" + QString::number(++index) + "()</span>);");
            result += createScript(qgraphicsitem_cast<DiagramItemBased *>(arrow->startItem()), index);
        }
    }
    script += getHtmlLine("\tnetwork.setInputData(" + QString::number(temp_index) +", x);");
    script += getHtmlLine("");
    if(item->GetInputData() != ""){
        script += getHtmlLine("\tvar input = " + item->GetInputData() + ";");
    }
    QStringList list = item->getSetting().script.split("\n");
    foreach(QString iter, list){
        for(int  i = 0; i < iter.size(); i++){
            if(iter[i] == "<"){
                iter = iter.mid(0, i) + "&lt;" + iter.mid(i + 1, iter.size());
            }
            if(iter[i] == ">"){
                iter = iter.mid(0, i) + "&gt;" + iter.mid(i + 1, iter.size());
            }
        }
        script += getHtmlLine("\t" + iter);
    }
    script += getHtmlLine("\t<span style=\"color: green;\">ProgressBar.ping();</span>") +
            getHtmlLine("\tnetwork.setOutputData(" + QString::number(temp_index) +", y);") +
            getHtmlLine("\treturn y;") +
            getHtmlLine("}") + "</p>";
    result += script;
    return result;
}
*/
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
    /*QString result = "";
    // block_list.push( new Block( function(){}, input, output, input_blocks ) );
    result += getHtmlLine( "\nblocks_list.push( new Block( " );
    result += getHtmlLine( "\tfunction( x ) {" );
    if( api->block_list[index]->GetInputData() != "")
        result += getHtmlLine( "\t\tvar input = " + api->based_block_list.at(index)->GetInputData() + ";");
    result += getHtmlLine( "\t\tvar y = [];" );
    QStringList list = api->based_block_list[index]->getSetting()->script.split("\n");
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
    foreach(Arrow* arrow, api->based_block_list[index]->getArrows()){
        if(arrow->startItem() != api->based_block_list[index]){
            temp += QString::number(api->based_block_list.indexOf(qgraphicsitem_cast<DiagramItemBased*>(arrow->startItem())));
            temp += ", ";
        }
    }
    if(temp[temp.size() - 2] == ",")
        temp.remove(temp.size() - 2, 1);

    temp += "]";

    result += getHtmlLine( "\t" + temp );
    result += getHtmlLine( "));\n" );
    return result;*/
}

QString OutputWidget::loadScript(QString path){
    QFile f(path);
    QScriptValue result;
    if(f.open(QIODevice::ReadOnly)){
        QString str = f.readAll();
        qDebug() << path + "  " + str;
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
        QString temp = loadScript(":/scripts/script.js");
        if(temp.length()){
            ui->textEdit_2->setText("Defult script: " + temp);
        }
    }

    if(ui->checkBox->isChecked()){
        QString temp = loadScript(":/scripts/XMLHttpRequest.js");
        if(temp.length()){
            ui->textEdit_2->setText("Defult script: " + temp);
        }
    }
    QString temp = loadScript(":/scripts/progress.js");
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
    temp = loadScript(":/scripts/block_logic.js");
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
