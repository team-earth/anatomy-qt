#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>
#include <QString>
#include <QGraphicsItem>

class Node : public QGraphicsItem
{
public:
    explicit Node(Node&& n) {}
    Node(QString text);
    QRectF boundingRect() const override;
//    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QString text_;
    std::vector<Node*> children_;
    Node* parentNode_;

};

#endif // NODE_H
