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

Node*  Node::addPeer()
{
    if (parentNode_)
    {
        return parentNode_->addChild();
    }

    return nullptr;
}

Node* Node::addChild()
{
    QGraphicsScene* scene = this->myQGraphicsPathItem_->scene();

    Node* child = new Node("NEW", this);

    child->childIndex = children_.size();
    this->children_.push_back(child);
    scene->addItem(child->getMyQGraphicsPathItem());

    MyQGraphicsTextItem* ti = child->getMyQGraphicsTextItem();
    ti->setEditor(this->myQGraphicsTextItem_->te_);

    return child;
}

