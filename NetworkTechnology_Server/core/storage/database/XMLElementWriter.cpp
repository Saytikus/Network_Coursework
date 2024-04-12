#include "XMLElementWriter.h"

XMLElementWriter::XMLElementWriter(QObject *parent)
    : QObject{parent}
{

}

void XMLElementWriter::writeint(QDomDocument domDocument, QDomElement element, QString newElementName, qint32 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}


void XMLElementWriter::writeUint(QDomDocument domDocument, QDomElement element, QString newElementName, quint32 value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(QString::number(value));
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}

void XMLElementWriter::writeText(QDomDocument domDocument, QDomElement element, QString newElementName, QString value) {
    QDomElement xmlRecord = domDocument.createElement(newElementName);
    QDomText recordValue = domDocument.createTextNode(value);
    xmlRecord.appendChild(recordValue);
    element.appendChild(xmlRecord);
}

void XMLElementWriter::writeTexts(QDomDocument domDocument, QDomElement element, QString newElementName, QList<QString> value) {
    for (qint32 i=0; i<value.size(); i++) {
        QDomElement xmlRecord = domDocument.createElement(newElementName);
        QDomText recordValue = domDocument.createTextNode(value[i]);
        xmlRecord.appendChild(recordValue);
        element.appendChild(xmlRecord);
    }
}
