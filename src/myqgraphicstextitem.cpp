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
    qDebug() << "cmLevelIn";
    MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());

    qDebug() << "MainWindow::centerNode_:" << MainWindow::centerNode_;
    qDebug() << "p->parentNode_" << p->parentNode_;
    qDebug() << "p" << p;
    MainWindow::centerNode_ = p;
    MainWindow::centerNode_->arcDegrees_ = 360;
    MainWindow::centerNode_->arcStartDegrees_ = 90;

    emit focusThisItem(this);
}

void MyQGraphicsTextItem::cmLevelUp()
{
    MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());
    qDebug() << "cmLevelUp p->parentNode_" << p->parentNode_;
    qDebug() << "cmLevelUp p" << p;

    MainWindow::centerNode_ = p->parentNode_;
    MainWindow::centerNode_->arcDegrees_ = 360;
    MainWindow::centerNode_->arcStartDegrees_ = 90;

    emit focusThisItem(this);
}

//void MyQGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "MyQGraphicsTextItem::mousePressEvent" << event;
//}



