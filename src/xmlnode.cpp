#include "xmlnode.h"

#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>

XmlNode::XmlNode()
{

}

bool XmlNode::readFile(QString fn)
{
    QFile file(fn);
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while (!xmlReader.isEndDocument())
        {
            if (xmlReader.isStartElement())
            {
                QString name = xmlReader.name().toString();

                // TODO: We're skipping non-"node" elements
                if (name == "node")
                {
                    readNode(xmlReader);
                }
//                else
//                {
//                    qDebug() << "node is not node, it is: " << name;
//                }
            }
            xmlReader.readNext();
        }
        if (xmlReader.hasError())
        {
            qDebug() << "XML error: " << xmlReader.errorString().data();
        }
    }
}


bool XmlNode::readNode(QXmlStreamReader& xmlReader)
{
    // gather all attributes
    for (int i = 0 ; i < xmlReader.attributes().size(); i++ )
    {
        QString name = xmlReader.attributes().at(i).name().toString();
        QString value = xmlReader.attributes().at(i).value().toString();

        if (name.toLower() == "text")
        {
            text_ = value;
        }
        else
        {
            attributes_[name] = value;
        }
    }

//    qDebug() << "text is" << xmlReader.text().toString();
    xmlReader.readNext();
//    qDebug() << "next text is" << xmlReader.text().toString();

    while(!xmlReader.isEndElement())
    {
        if (xmlReader.isStartElement())
        {
            QString name = xmlReader.name().toString();

            if (name.toLower() == "node")
            {
                XmlNode* n = new XmlNode();
                this->children_.append(n);
                n->readNode(xmlReader);
            }
            else
            {
                readOther(xmlReader);
            }
        }
        // TODO: "\n" is considered a node
//        else
//        {
//            qDebug()
//                    << "Hmm, XmlNode::readNode is neither start nor stop element: "
//            << xmlReader.text().toString();
//        }
        xmlReader.readNext();
    }

    return true;
}

bool XmlNode::readOther(QXmlStreamReader& xmlReader)
{
    // gather all attributes
    for (int i = 0 ; i < xmlReader.attributes().size(); i++ )
    {
        QString name = xmlReader.attributes().at(i).name().toString();
        QString value = xmlReader.attributes().at(i).value().toString();

//        qDebug() << "Other node attribute " << name << " = " << value;
    }

    while(!xmlReader.isEndElement())
    {
        xmlReader.readNext();
    }

    return true;
}

void XmlNode::printNode(XmlNode* node)
{
    static int indent=0;
    QString tab = "";
    for (int i = 0; i < indent; i++)
    {
        tab += "  ";
    }

    qDebug() << tab << node->text_;
    indent++;
    for (int i = 0 ; i < node->children_.size(); i++)
    {
        printNode(node->children_.at(i));
    }
    indent--;
}
