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

void MyQGraphicsTextItem::cmFocus()
{
    qDebug() << "MyQGraphicsTextItem::cmFocus";
    MainWindow::globalDegrees_ =
            node_->myQGraphicsPathItem_->arcStartDegrees_ +
            node_->myQGraphicsPathItem_->arcDegrees_/2;

    emit focusThisItem(this);
}

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
#if 0
    MainWindow::centerNode_ = this->node_;
    MainWindow::centerMyQGraphicsPathItem_->arcDegrees_ = 360;
    MainWindow::centerMyQGraphicsPathItem_->arcStartDegrees_ = 90;

    emit focusThisItem(this);
#endif
}

void MyQGraphicsTextItem::cmLevelOut()
{
#if 0
    MyQGraphicsPathItem* this_p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());

    if (this_p)
    {
        MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(this_p->parentNode_);

        if (p)
        {
            MainWindow::centerMyQGraphicsPathItem_ = p;
            MainWindow::centerMyQGraphicsPathItem_->arcDegrees_ = 360;
            MainWindow::centerMyQGraphicsPathItem_->arcStartDegrees_ = 90;
        }

        emit focusThisItem(this);
    }
#endif
}
