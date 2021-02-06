#include "myqgraphicstextitem.h"
#include "myqgraphicspathitem.h"

void MyQGraphicsTextItem::updateText()
{
    if (te_)
    {
        this->setHtml(te_->toHtml());
    }
}

void MyQGraphicsTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent * e)
{
    MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());
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

void MyQGraphicsTextItem::cmLevelIn()
{
    MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());

    MainWindow::centerNode_ = p;
    MainWindow::centerNode_->arcDegrees_ = 360;
    MainWindow::centerNode_->arcStartDegrees_ = 90;

    emit focusThisItem(this);
}

void MyQGraphicsTextItem::cmLevelOut()
{
    MyQGraphicsPathItem* this_p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());

    if (this_p)
    {
        MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(this_p->parentNode_);

        if (p)
        {
            MainWindow::centerNode_ = p;
            MainWindow::centerNode_->arcDegrees_ = 360;
            MainWindow::centerNode_->arcStartDegrees_ = 90;
        }

        emit focusThisItem(this);
    }
}
