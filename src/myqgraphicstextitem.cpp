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
    node_->myQGraphicsPathItem_->contextMenuEvent(e);
//    MyQGraphicsPathItem* p = dynamic_cast<MyQGraphicsPathItem*>(parentItem());
//    p->contextMenuEvent(e);
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

void MyQGraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static int count = 0;
    if (toPlainText().left(3) == "Cyn" || toPlainText().left(3) == "Rap")
    {
        qDebug() << "pa:" << transform() << this->toPlainText();
    }
    QGraphicsTextItem::paint(painter, option, widget);
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
    MainWindow::centerNode_ = node_;
    MainWindow::centerNode_->myQGraphicsPathItem_->arcDegrees_ = 360;
    MainWindow::centerNode_->myQGraphicsPathItem_->arcStartDegrees_ = 90;

    emit focusThisItem(this);
}

void MyQGraphicsTextItem::cmLevelOut()
{
    if (MainWindow::centerNode_->parentNode_)
    {
        MainWindow::centerNode_ = MainWindow::centerNode_->parentNode_;
        MainWindow::centerNode_->myQGraphicsPathItem_->arcDegrees_ = 360;
        MainWindow::centerNode_->myQGraphicsPathItem_->arcStartDegrees_ = 90;

        emit focusThisItem(this);
    }
}
