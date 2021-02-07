#ifndef MYQGRAPHICSPATHITEM_H
#define MYQGRAPHICSPATHITEM_H

#include <string>
#include <vector>
#include <memory>
#include <QString>
#include <QDebug>
#include <QEvent>
#include <QGraphicsPathItem>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <unordered_map>

class MyQGraphicsPathItem;
class Node;

class MyQGraphicsPathItem : public QGraphicsPathItem
{
    friend class MyQGraphicsTextItem;
public:
    MyQGraphicsPathItem(Node* node, QString text);
    QRectF boundingRect() const override;
    QPainterPath shape() const override { return path_; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* e) override;

    void cacheLineage();

    std::unordered_map<MyQGraphicsPathItem*, int> lineage_;
//    void initContextMenu();
    void cmFocus();
    void cmLevelIn();
    void cmLevelOut();

    QMenu* contextMenu_;
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
    Node* node_;
    QString text_;
    std::vector<MyQGraphicsPathItem*> children_;
    MyQGraphicsPathItem* parentMyQGraphicsPathItem_;
    size_t childIndex;
    QRectF bbox_;
    QPainterPath path_;
    qreal z_;
    int depth_;

    qreal arcDegrees_;
    qreal arcStartDegrees_;
//    QGraphicsTextItem textItem_;

};


#endif // MYQGRAPHICSPATHITEM_H
