#include "basedblocksetting.h"

BasedBlockSetting::BasedBlockSetting()
{

}

QJsonValue BasedBlockSetting::jsonValFromPixmap(const QPixmap &p) {
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG");
  auto const encoded = buffer.data().toBase64();
  return {QLatin1String(encoded)};
}

QPixmap BasedBlockSetting::pixmapFrom(const QJsonValue &val) {
  auto const encoded = val.toString().toLatin1();
  QPixmap p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
  return p;
}

void BasedBlockSetting::setSettingFromJson(QString str){
    QJsonDocument json = QJsonDocument::fromJson(str.toUtf8());
    if(json.isObject()){
        setSettingFromJson(json["data"]);
    }
}

void BasedBlockSetting::setSettingFromJson(QJsonValue value){
    if(value.isObject()){
        name = value["name"].toString();
        type_image = value["type_img"].toString();
        label = value["label"].toBool();
        label_text = value["label_text"].toString();
        line_edit = value["line_edit"].toBool();
        line_edit_text = value["line_edit_text"].toString();
        script = value["script"].toString();
        image = pixmapFrom(value["image"]);
    }
}

QJsonObject BasedBlockSetting::getJsonFromSetting(){

    QJsonObject obj;

    QJsonObject temp_obj;
    temp_obj.insert("name", QJsonValue(name));
    temp_obj.insert("type_img", QJsonValue(type_image));
    temp_obj.insert("label", QJsonValue(label));
    temp_obj.insert("label_text", QJsonValue(label_text));
    temp_obj.insert("line_edit", QJsonValue(line_edit));
    temp_obj.insert("line_edit_text", QJsonValue(line_edit_text));
    temp_obj.insert("script", QJsonValue(script));
    temp_obj.insert("image", jsonValFromPixmap(image));

    obj.insert("type", QJsonValue("basic"));
    obj.insert("data", QJsonValue(temp_obj));

    return obj;
}

