#include "mynetwork.h"

MyNetwork::MyNetwork(QWidget *parent)
    : QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(getResponse(QNetworkReply*)));
}

void MyNetwork::setUrl(QString str){
    url.setUrl(str);
}

void MyNetwork::open(QString type, QString path){
    this->type = type;
    this->path = path;
}

void MyNetwork::setRequestHeader(QString name, QString value){
    QVector<QString> temp = {name, value};
    headers.push_back(temp);
}

void MyNetwork::send(QString data){
    request.setUrl(url);

    for(int i = 0; i < headers.size(); i++){
        request.setRawHeader(headers[i][0].toUtf8(), headers[i][1].toUtf8());
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    if(type == "POST"){
        manager->post(request, data.toUtf8());
    }else{
        manager->get(request);
    }
}

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

QString MyNetwork::waitAnswer(){
    while(answerflag == ""){
        delay(100);
    }
    QString result = answerflag;
    answerflag = "";
    return result;
}

void MyNetwork::getResponse(QNetworkReply* reply){
    answerflag = reply->readAll();
}

