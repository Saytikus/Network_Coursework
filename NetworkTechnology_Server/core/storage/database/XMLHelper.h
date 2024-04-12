#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QObject>

#include <QtGlobal>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QString>

class XMLHelper : public QObject {

    Q_OBJECT

    public:
        explicit XMLHelper(QObject *parent = nullptr);

        /**
         * @brief checkFile - функция проверки файла для чтения
         * @param databasePath - путь xml-файла
         **/
        static bool checkFile(QString databasePath);

        /**
          * @brief writeXMLHeader - функция добавления заголовка в документ
          * @param domDocument - документ
          **/
         static void writeXMLHeader(QDomDocument *domDocument);

         /**
          * @brief writeXMLStructTree - функция выстраивает структуру в файле xmlDocument->Database->имя субэлемента
          * @param domDocument - документ
          * @param nameElement - имя субэлемента
          **/
         static QDomElement writeXMLStructTree(QDomDocument *domDocument, QString nameElement);

         /**
          * @brief searchSingleNode - функция проверяет наличие указанной node в элементе
          * @param element - элемент дерева, в котором будет осуществлен node
          * @param searchElementName - тэг, элемент для поиска соответсвующей node
          **/
         static bool checkSingleNode(QDomElement element, QString searchElementName);

         /**
          * @brief readSingleNode - функция чтения одной node по тэгу
          * @param element - элемент дерева, из которого требуется считать node
          * @param searchElementName - тэг, элемент для поиска соответсвующей node
          **/
         static QDomElement readSingleNode(QDomElement element, QString searchElementName);

         /**
          * @brief readMultiNode - функция чтения нескольких node по тэгу
          * @param element - элемент дерева, из которого требуется считать node
          * @param searchElementName - тэг, элемент для поиска соответсвующих node
          **/
         static QList<QDomElement> readMultiNode(QDomElement element, QString searchElementName);

    signals:

};

#endif // XMLHELPER_H
