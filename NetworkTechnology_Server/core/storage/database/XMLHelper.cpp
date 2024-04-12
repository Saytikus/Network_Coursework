#include "XMLHelper.h"

#include <QFile>
#include "common/logs/Logger.h"
#include <QXmlStreamReader>

XMLHelper::XMLHelper(QObject *parent)
    : QObject{parent}
{

}

bool XMLHelper::checkFile(QString databasePath) {

    QFile file(databasePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        Logger::recordLog("XMLHelper", "Файл базы данных не открылся");
        return false;
    }

    QDomDocument doc;

    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }

    file.seek(0); // Сбросить позицию чтения файла до начала

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::Invalid) {
            Logger::recordLog("XMLHelper", "Файл базы данных поврежден");
            return false;
        }
    }

    if (xml.hasError()) {
        Logger::recordLog("XMLHelper", "Ошибка XML: " + xml.errorString());
        return false;
    }

    file.close();

    return true;

}

void XMLHelper::writeXMLHeader(QDomDocument *domDocument) {
    QDomNode node(domDocument->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));
    domDocument->insertBefore(node,domDocument->firstChild());
}

QDomElement XMLHelper::writeXMLStructTree(QDomDocument *domDocument, QString nameElement) {
    QDomElement root = domDocument->createElement("xmlDocument");
    domDocument->appendChild(root);
    QDomElement databaseElement = domDocument->createElement("Database");
    root.appendChild(databaseElement);
    QDomElement underElement = domDocument->createElement(nameElement);
    databaseElement.appendChild(underElement);
    return underElement;
}

bool XMLHelper::checkSingleNode(QDomElement element, QString searchElementName) {
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs = element.childNodes();

    for (qint32 i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент нод
        QDomNode domNode = childs.at(i);

        // Проверка на то, что нод является элементом
        if (!domNode.isElement()) {
            Logger::recordLog("XMLHelper", "Ошибка чтения QDomElement из файла");
            return false;
        }
        // Кастуем нод в элемент
        QDomElement domElement = domNode.toElement();

        // Проверка каста
        if (domElement.isNull()) {
            Logger::recordLog("XMLHelper", "Ошибка преобразования QDomNode в QDomElement");
            return false;
        }

        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        QString nodeName = domElement.nodeName();
        if (domElement.nodeName() == searchElementName) {
            Logger::recordLog("XMLHelper", "QDomElement " + nodeName + " успешно проверен");
            return true;
        }

    }

    Logger::recordLog("XMLHelper", "Ошибка, не найден QDomElement");

    return false;
}

QDomElement XMLHelper::readSingleNode(QDomElement element, QString searchElementName) {
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs= element.childNodes();
    for (qint32 i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);

        // Проверка на то, что нод является элементом
        if (!domNode.isElement()) {
            Logger::recordLog("XMLHelper", "Ошибка чтения QDomElement из файла");
            return QDomElement();
        }

        // Кастуем нод в элемент
        QDomElement domElement = domNode.toElement();

        // Проверка каста
        if (domElement.isNull()) {
            Logger::recordLog("XMLHelper", "Ошибка преобразования QDomNode в QDomElement");
            return QDomElement();
        }

        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        QString nodeName = domElement.nodeName();
        if (domElement.nodeName() == searchElementName) {
            Logger::recordLog("XMLHelper", "QDomElement " + nodeName + " успешно прочтен");
            return domElement;
        }

    }

    Logger::recordLog("XMLHelper", "Ошибка, не найден QDomElement");

    return QDomElement();
}

QList<QDomElement> XMLHelper::readMultiNode(QDomElement element, QString searchElementName) {

    QList<QDomElement> elements;
    //Взять список всех дочерних, входящих в неё нод
    QDomNodeList childs = element.childNodes();
    for (qint32 i = 0; i < childs.size() ; i++) {
        //Перебираем по 1 входящий в 'Database элемент ноде
        QDomNode domNode = childs.at(i);
        //Если нода это элемент вообще (может быть комментарий или кракозябра
        if (!domNode.isElement()) {
            Logger::recordLog("XMLHelper", "Ошибка чтения QDomElement из файла");
            return QList<QDomElement>();
        }

        //Так как это элемент, можно ноду для поиска скастовать в элемент для работы
        QDomElement domElement = domNode.toElement();

        //на всякий случай, проверяем, что он нормально скастовался
        if (domElement.isNull()) {
            Logger::recordLog("XMLHelper", "Ошибка преобразования QDomNode в QDomElement");
            return QList<QDomElement>();
        }
        //Если элемент входяший в element это searchElementName, то читаем его как корневую группу
        if (domElement.nodeName() == searchElementName) {
            Logger::recordLog("XMLHelper", "QDomElement " + domElement.nodeName() + " успешно прочтен");
            elements.append(domElement);
        }

    }

    return elements;
}
