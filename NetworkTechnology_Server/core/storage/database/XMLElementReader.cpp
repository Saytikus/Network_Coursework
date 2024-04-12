#include "XMLElementReader.h"

XMLElementReader::XMLElementReader(QObject *parent)
    : QObject{parent}
{

}

qint32 XMLElementReader::readint(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toInt();
}

quint32 XMLElementReader::readUint(QDomElement element, QString searchElementName) {
    return element.elementsByTagName(searchElementName).at(0).toElement().text().toUInt();
}


QString XMLElementReader::readText(QDomElement element, QString searchElementName) {
    QString result = element.elementsByTagName(searchElementName).at(0).toElement().text();
    return element.elementsByTagName(searchElementName).at(0).toElement().text();
}

QList<QString> XMLElementReader::readTexts(QDomElement element, QString searchElementName) {
    QList<QString> values;
    QDomNodeList elements = element.elementsByTagName(searchElementName);
    for (qint32 i = 0; i < elements.size(); i++ ) {
        QDomNode em = elements.at(i);
        values.append(em.toElement().text());
    }
    return values;
}
