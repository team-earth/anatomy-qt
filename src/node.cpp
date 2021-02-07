#include "node.h"
#include "myqgraphicspathitem.h"
#include "myqgraphicstextitem.h"
#include <QPointF>
#include <QString>

Node::Node(QString text, Node* parentNode)
    : parentNode_(parentNode)
{
  myQGraphicsPathItem_ = new MyQGraphicsPathItem(this);
  myQGraphicsPathItem_->setPos(QPointF(0, 0));

  myQGraphicsTextItem_ = new MyQGraphicsTextItem(this);
  myQGraphicsTextItem_->setHtml(text);

  if (parentNode_ == nullptr)
  {
      depth_ = 0;
  }
  else
  {
      depth_ = parentNode_->depth_ + 1;
  }

  cacheLineage();
}

MyQGraphicsPathItem* Node::getMyQGraphicsPathItem() const
{
    return myQGraphicsPathItem_;
}

MyQGraphicsTextItem* Node::getMyQGraphicsTextItem() const
{
    return myQGraphicsTextItem_;
}

void Node::cacheLineage()
{
    if (parentNode_)
    {
        Node* p = parentNode_;

        while (p)
        {
            lineage_[p] = p->depth_;
            p = p->parentNode_;
        }
    }
}
