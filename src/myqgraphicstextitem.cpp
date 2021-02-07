#include "myqgraphicstextitem.h"
#include "myqgraphicspathitem.h"

MyQGraphicsTextItem::MyQGraphicsTextItem(Node* node)
    : QGraphicsTextItem(node->myQGraphicsPathItem_),
      node_(node),
      te_(nullptr)
{
//        connect(QGraphicsTextItem, &QGraphicsTextItem::, this, &TextEdit::setText);
//        setFlag(QGraphicsItem::ItemIsFocusable, false);
//        setFlag(QGraphicsItem::ItemIsSelectable, false);
//        setCursor(Qt::BlankCursor);
    static int i=0;

    id_ = i++;

    setTextInteractionFlags(Qt::TextEditorInteraction);

    QAction *focusAction = new QAction("Focus");
    QAction *levelInAction = new QAction("Level In");
    QAction *levelUpAction = new QAction("Level Out");
    QAction *addPeer = new QAction("Add Peer");
    QAction *addChild = new QAction("Add Child");

    contextMenu_ = new QMenu();
    contextMenu_->addAction(focusAction);
    contextMenu_->addAction(levelInAction);
    contextMenu_->addAction(levelUpAction);
    contextMenu_->addAction(addPeer);
    contextMenu_->addAction(addChild);

    connect(focusAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmFocus);
    connect(levelInAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmLevelIn);
    connect(levelUpAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmLevelOut);
    connect(addPeer, &QAction::triggered, this, &MyQGraphicsTextItem::addPeer);
    connect(addChild, &QAction::triggered, this, &MyQGraphicsTextItem::addChild);

    connect(this, &MyQGraphicsTextItem::focusThisItem, MainWindow::instance(), &MainWindow::refresh);
}

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

void MyQGraphicsTextItem::addPeer()
{
    node_->addPeer();
}

void MyQGraphicsTextItem::addChild()
{
    node_->addChild();
}

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
//    static int count = 0;
//    if (toPlainText().left(3) == "Cyn" || toPlainText().left(3) == "Rap")
//    {
//        qDebug() << "pa:" << transform() << this->toPlainText();
//    }
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
