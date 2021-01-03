#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>
#include <QString>
#include <QGraphicsPathItem>

class Node : public QGraphicsPathItem
{
public:
    Node(QString text, Node* parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override { return path_; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


protected:
    bool sceneEvent(QEvent*);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QString text_;
    std::vector<Node*> children_;
    Node* parentNode_;
    size_t childIndex;
    bool selected_;
    QRectF bbox_;
    QPainterPath path_;
    qreal z_;
//    QGraphicsTextItem textItem_;

};

#endif // NODE_H
