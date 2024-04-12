#ifndef XMLELEMENTREADER_H
#define XMLELEMENTREADER_H

#include <QObject>

#include <QtGlobal>
#include <QtXml/QDomElement>
#include <QString>

class XMLElementReader : public QObject {

    Q_OBJECT

    public:
        explicit XMLElementReader(QObject *parent = nullptr);

    /**
        * @brief read *TYPE* - блок функций чтения записей по тэгу
        * @param element - элемент дерева, из которого требуется считать запись
        * @param searchElementName - тэг, элемент для поиска соответсвующей записи
        **/
       static qint32 readint(QDomElement element, QString searchElementName);

       static quint32 readUint(QDomElement element, QString searchElementName);

       static QString readText(QDomElement element, QString searchElementName);

       static QList<QString> readTexts(QDomElement element, QString searchElementName);

    signals:

};

#endif // XMLELEMENTREADER_H
