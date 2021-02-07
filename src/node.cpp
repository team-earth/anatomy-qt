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

  myQGraphicsTextItem_ = new MyQGraphicsTextItem(myQGraphicsPathItem_);
}

MyQGraphicsPathItem* Node::getMyQGraphicsPathItem() const
{
    return myQGraphicsPathItem_;
}

MyQGraphicsTextItem* Node::getMyQGraphicsTextItem() const
{
    return myQGraphicsTextItem_;
}
