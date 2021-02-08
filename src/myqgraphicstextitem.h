#ifndef MYQGRAPHICSTEXTITEM_H
#define MYQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include <QStyle>
#include <QMenu>
#include <QStyleOptionGraphicsItem>
#include "myqtextedit.h"
#include "mainwindow.h"
#include "node.h"

class MyQTextEdit;

class MyQGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

    friend class Node;
public:

    MyQGraphicsTextItem(Node* node);
    int id_;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void cmLevelIn();
    void cmLevelOut();
    void cmSpotlight();
    void addPeer();
    void addChild();

    void updateText();

    void setEditor(MyQTextEdit* te)
    {
        te_ = te;
        connect(this, &MyQGraphicsTextItem::selected, te_, &MyQTextEdit::setText);
    }

    QMenu* contextMenu_;
signals:
    void selected(QString);
    void focusThisItem(const MyQGraphicsTextItem*);


protected:
    Node* node_;
    MyQTextEdit* te_;

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
//    {
//        QStyleOptionGraphicsItem myOption(*option);
//        myOption.state &= !QStyle::State_Selected;
//        QGraphicsTextItem::paint(painter, &myOption, widget);
//    }

public:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * e) override;
//    bool sceneEvent(QEvent *) override;
//    bool sceneEvent(QEvent* e)
//    {
//        qDebug() << "MyQGraphicsTextItem::sceneEvent" << e->type();
//        return QGraphicsTextItem::sceneEvent(e);
//    }
    void focusInEvent(QFocusEvent *event) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYQGRAPHICSTEXTITEM_H
