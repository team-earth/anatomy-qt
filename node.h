#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>
#include <QString>
#include <QDebug>
#include <QEvent>
#include <QGraphicsPathItem>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include "textedit.h"

class Node : public QGraphicsPathItem
{
public:
    Node(QString text, Node* parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override { return path_; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


protected:
//    bool sceneEvent(QEvent*);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
//    {
//        parentWidget()->mousePressEvent();
//    }
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//      void focusInEvent(QFocusEvent *event) override
//      {
//          parentWidget()->setSelected(true);
////          QGraphicsPathItem::focusInEvent(event);
//      }

public:
    QString text_;
    std::vector<Node*> children_;
    Node* parentNode_;
    size_t childIndex;
    QRectF bbox_;
    QPainterPath path_;
    qreal z_;
//    QGraphicsTextItem textItem_;

};

class MyQGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:

    MyQGraphicsTextItem(QGraphicsItem* parent) : QGraphicsTextItem(parent)
    {
//        connect(QGraphicsTextItem, &QGraphicsTextItem::, this, &TextEdit::setText);
    }

signals:
    void selected(QString);

public:
//    bool sceneEvent(QEvent* e)
//    {
//        qDebug() << "MyQGraphicsTextItem::sceneEvent" << e->type();
//        return QGraphicsTextItem::sceneEvent(e);
//    }
    void focusInEvent(QFocusEvent *event) override
    {
        emit selected(this->toHtml());
        QList<QGraphicsItem*> items = scene()->selectedItems();
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i] != parentItem())
            {
                items[i]->setSelected(false);
            }
        }
        if (parentItem() && !parentItem()->hasFocus())
        {
            parentItem()->setSelected(true);
        }
        QGraphicsTextItem::focusInEvent(event);
    }
};

#endif // NODE_H
