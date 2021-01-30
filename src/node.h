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
    friend class MyQGraphicsTextItem;
public:
    Node(QString text, Node* parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override { return path_; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* e) override;
//    void contextMenuEvent(QContextMenuEvent *event) override;

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
    int depth_;

    qreal arcDegrees_;
    qreal arcStartDegrees_;
//    QGraphicsTextItem textItem_;

};


#endif // NODE_H
