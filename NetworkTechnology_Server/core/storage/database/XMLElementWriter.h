#ifndef XMLELEMENTWRITER_H
#define XMLELEMENTWRITER_H

#include <QObject>

#include <QtGlobal>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QString>

class XMLElementWriter : public QObject {

    Q_OBJECT

    public:
        explicit XMLElementWriter(QObject *parent = nullptr);


    /**
         * @brief write *TYPE* - блок функций чтения записей по тэгу
         * @param domDocument - dom документ xml-файла, в который пишется всё
         * @param element - элемент дерева, в которого будет производится запись
         * @param newElementName - название нового элемента
         * @param value - значение нового элемента
         **/

        static void writeint(QDomDocument domDocument, QDomElement element, QString newElementName, qint32 value);

        static void writeUint(QDomDocument domDocument, QDomElement element, QString newElementName, quint32 value);

        static void writeText(QDomDocument domDocument, QDomElement element, QString newElementName, QString value);

        static void writeTexts(QDomDocument domDocument, QDomElement element, QString newchElementName, QList<QString> value);

    signals:

};

#endif // XMLELEMENTWRITER_H
