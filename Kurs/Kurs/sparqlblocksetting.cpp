#include "sparqlblocksetting.h"
#include <QtMath>
#include <QUrl>

SparqlBlockSetting::SparqlBlockSetting()
{

    int n = 32;
    double Pi = 3.1415926535;
    double step = 2 * Pi / n;
    int razmer = 50;
    int radius = 20;

    for( int i = 0; i < n / 4; i++){
        polygon << QPointF( radius * cos( i * step ) + razmer - radius,
                            radius * sin( i * step ) + razmer - radius);
    }
    polygon << QPointF( -(razmer - radius), razmer );

    for( int i = n / 4; i < 2 * n / 4; i++){
        polygon << QPointF( radius * cos( i * step ) - (razmer - radius) ,
                            radius * sin( i * step ) + razmer - radius);
    }
    polygon << QPointF( -razmer, -(razmer - radius) );

    for( int i = 2 * n / 4; i < 3 * n / 4; i++){
        polygon << QPointF( radius * cos( i * step ) - (razmer - radius) ,
                            radius * sin( i * step ) - (razmer - radius));
    }
    polygon << QPointF( razmer - radius, -razmer );

    for( int i = 3 * n / 4; i < 4 * n / 4; i++){
        polygon << QPointF( radius * cos( i * step ) + razmer - radius ,
                            radius * sin( i * step ) - (razmer - radius));
    }
    polygon << QPointF( razmer, razmer - radius );

  /*polygon << QPointF( razmer * cos( 0 ), 35 * sin( 0 ) );

    for( int i = 0; i < n; i++){
        polygon << QPointF( 45 * cos( i * step ), 30 * sin( i * step ) );
    }
    polygon << QPointF( 45 * cos( 0 ), 30 * sin( 0 ) );
*/
}

BasedBlockSetting* SparqlBlockSetting::ConvertToBasedBlockSetting()
{
    QString script =
            "var xmlHttp = new XMLHttpRequest(network);\n"
            "xmlHttp.setUrl(\"http://localhost:3030/nuclear/sparql\");\n"
            "xmlHttp.open(\"POST\", \"/\");\n"
            "xmlHttp.setRequestHeader(\"Connection\", \"keep-alive\");\n"
            "xmlHttp.setRequestHeader(\"Accept\", \"application/sparql-results+json\");\n"
            "var answer = xmlHttp.send(";

    QVector<QString> list;
    QString request = "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
            "PREFIX owl: <http://www.w3.org/2002/07/owl#>\n"
            "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
            "PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>\n"
            "PREFIX : <http://www.semanticweb.org/SEARCH/ontologies/2021/4/OICA_project#>\n\n"
            "SELECT ";

    QString body;
    for( auto line : lines )
    {
        list.push_back( blocks[line.startBlock].text );
        body += list.back();
        body += " " + line.text;
        list.push_back( blocks[line.endBlock].text );
        body += " " + list.back();
        body += ".\n";
    }

    for ( const auto& str : list )
    {
        if ( '?' == str[0] )
        {
            request += str + " ";
        }
    }

    request += "\nWHERE\n"
            "  {\n";
    request += "  " + body;
    request += "} LIMIT " + QString::number( limit );

    BasedBlockSetting* setting = new BasedBlockSetting();
    setting->label = false;
    setting->line_edit = false;
    setting->name = "SPARQL";
    setting->script = script + "\"query=" + QUrl::toPercentEncoding(request) + "\");\ny.push(answer);";
    qDebug() << request;
    return setting;
}

void SparqlBlockSetting::setSettingFromJson( const QString& str )
{
    QJsonDocument json = QJsonDocument::fromJson( str.toUtf8() );
    if( json.isObject() ){
        setSettingFromJson( json["data"] );
    }
}

void SparqlBlockSetting::setSettingFromJson( const QJsonValue& value )
{
    if ( value.isObject() )
    {
        name = value["name"].toString();
        //type_image = value["type_img"].toString();
        image = pixmapFromJsonVal( value["image"] );
        limit = value["limit"].toInt();

        blocks.clear();
        for ( const QJsonValue& block : value["blocks"].toArray() )
        {
            blocks.push_back( { block["text"].toString(),
                                QPointF( block["pos_x"].toDouble(), block["pos_y"].toDouble() ) } );
        }

        lines.clear();
        for ( const QJsonValue& line : value["lines"].toArray() )
        {
            lines.push_back( { line["start_block"].toInt(), line["end_block"].toInt(), line["text"].toString() } );
        }
    }
}
/*
    struct LineSaver
    {
        int startBlock;
        int endBlock;
        QString text;
    };

    struct BlockSaver
    {
        QString text;
        QPointF pos;
    };

    QVector<BlockSaver> blocks;
    QVector<LineSaver> lines;
    int limit;
    QPixmap image;
    QString name;

    QPolygonF polygon;
*/
QJsonObject SparqlBlockSetting::getJsonFromSetting()
{
    QJsonObject obj;

    QJsonObject data;
    data.insert( "name", QJsonValue( name ) );
    data.insert( "type_img", QJsonValue( "" ) );
    data.insert( "image", jsonValFromPixmap( image ) );
    data.insert( "limit", QJsonValue( limit ) );

    QJsonArray array_blocks;
    for ( const auto& next_block : blocks )
    {
        QJsonObject temp_obj;
        temp_obj.insert( "text", QJsonValue( next_block.text ) );
        temp_obj.insert( "pos_x", QJsonValue( next_block.pos.x() ) );
        temp_obj.insert( "pos_y", QJsonValue( next_block.pos.y() ) );
        array_blocks.push_back( temp_obj );
    }
    data.insert( "blocks", array_blocks );

    QJsonArray array_lines;
    for ( const auto& next_line : lines )
    {
        QJsonObject temp_obj;
        temp_obj.insert( "text", QJsonValue( next_line.text ) );
        temp_obj.insert( "start_block", QJsonValue( next_line.startBlock ) );
        temp_obj.insert( "end_block", QJsonValue( next_line.endBlock ) );
        array_lines.push_back( temp_obj );
    }
    data.insert( "lines", array_lines );

    obj.insert( "type", QJsonValue( "sparql" ) );
    obj.insert( "data", QJsonValue( data ) );
    return obj;
}

QJsonValue SparqlBlockSetting::jsonValFromPixmap( const QPixmap &p )
{
    QBuffer buffer;
    buffer.open( QIODevice::WriteOnly );
    p.save( &buffer, "PNG" );
    auto const encoded = buffer.data().toBase64();
    return { QLatin1String( encoded ) };
}

QPixmap SparqlBlockSetting::pixmapFromJsonVal( const QJsonValue &val )
{
    auto const encoded = val.toString().toLatin1();
    QPixmap p;
    p.loadFromData( QByteArray::fromBase64( encoded ), "PNG" );
    return p;
}
