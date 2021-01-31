#include "myqgraphicstextitem.h"
#include "node.h"

void MyQGraphicsTextItem::updateText()
{
    if (te_)
    {
        this->setHtml(te_->toHtml());
    }
}

void MyQGraphicsTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent * e)
{
    Node* p = dynamic_cast<Node*>(parentItem());
    p->contextMenuEvent(e);
}

//bool MyQGraphicsTextItem::sceneEvent(QEvent *e)
//{
//    qDebug() << "MyQGraphicsTextItem::sceneEvent" << e;
//    return QGraphicsTextItem::sceneEvent(e);
//}

void MyQGraphicsTextItem::focusInEvent(QFocusEvent *event)
{
    te_->connectMe(this);

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

//void MyQGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "MyQGraphicsTextItem::mousePressEvent" << event;
//}



