#include "node.h"
#include "myqgraphicspathitem.h"
#include "myqgraphicstextitem.h"
#include <QPointF>
#include <QString>

Node::Node(QString text, Node* parentNode)
    : parentNode_(parentNode)
{
  myQGraphicsPathItem_ = new MyQGraphicsPathItem(this, text);
  myQGraphicsPathItem_->setPos(QPointF(0, 0));
}

MyQGraphicsPathItem* Node::getMyQGraphicsPathItem() const
{
    return myQGraphicsPathItem_;
}
