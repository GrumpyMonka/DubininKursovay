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
    request += "} LIMIT 10";

    BasedBlockSetting* setting = new BasedBlockSetting();
    setting->label = false;
    setting->line_edit = false;
    setting->name = "SPARQL";
    setting->script = script + "\"query=" + QUrl::toPercentEncoding(request) + "\");\ny.push(answer);";
    return setting;
}
