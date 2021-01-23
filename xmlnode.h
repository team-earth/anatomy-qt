#ifndef XMLNODE_H
#define XMLNODE_H

#include <QString>
#include <QVector>
#include <QXmlStreamReader>
#include <QMap>

class XmlNode
{
public:
    XmlNode();

    enum TYPE { NODE, NOTE };

    bool readFile(QString);

    bool readNode(QXmlStreamReader&);
    bool readOther(QXmlStreamReader&);

    QString text_;

    static void printNode(XmlNode*);
    QVector<XmlNode*> children_;

protected:


    TYPE type_;


//    QString icon_;
//    QString hook_;
//    QString font_;
//    QString edge_;
//    QString cloud_;
//    QString linktarget_;
//    QString attributeLayout_;
//    QString attribute_;
//    QString arrowLink_;

    QMap<QString,QString> attributes_;
};

#endif // XMLNODE_H
