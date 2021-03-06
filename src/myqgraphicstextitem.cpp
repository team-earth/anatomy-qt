#include "myqgraphicstextitem.h"
#include "myqgraphicspathitem.h"

MyQGraphicsTextItem::MyQGraphicsTextItem(Node* node)
    : QGraphicsTextItem(node->myQGraphicsPathItem_),
      node_(node),
      myQTextEdit_(nullptr)
{
//        connect(QGraphicsTextItem, &QGraphicsTextItem::, this, &TextEdit::setText);
//        setFlag(QGraphicsItem::ItemIsFocusable, false);
//        setFlag(QGraphicsItem::ItemIsSelectable, false);
//        setCursor(Qt::BlankCursor);
    static int i=0;

    id_ = i++;

    setTextInteractionFlags(Qt::TextEditorInteraction);

    QAction *spotlightAction = new QAction("Spotlight");
    QAction *levelInAction = new QAction("Level In");
    QAction *levelUpAction = new QAction("Level Out");
    QAction *addPeer = new QAction("Add Peer");
    QAction *addChild = new QAction("Add Child");

    contextMenu_ = new QMenu();
    contextMenu_->addAction(spotlightAction);
    contextMenu_->addAction(levelInAction);
    contextMenu_->addAction(levelUpAction);
    contextMenu_->addAction(addPeer);
    contextMenu_->addAction(addChild);

    connect(spotlightAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmSpotlight);
    connect(levelInAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmLevelIn);
    connect(levelUpAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmLevelOut);
    connect(addPeer, &QAction::triggered, this, &MyQGraphicsTextItem::addPeer);
    connect(addChild, &QAction::triggered, this, &MyQGraphicsTextItem::addChild);

    connect(this, &MyQGraphicsTextItem::focusThisItem, MainWindow::instance(), &MainWindow::refresh);
}

void MyQGraphicsTextItem::updateText()
{
    if (myQTextEdit_)
    {
        this->setHtml(myQTextEdit_->toHtml());
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
    Node* peer = node_->addPeer();

    if (peer)
        peer->getMyQGraphicsTextItem()->cmSpotlight();
}

void MyQGraphicsTextItem::addChild()
{
    Node* child = node_->addChild();

    if (child)
        child->getMyQGraphicsTextItem()->cmSpotlight();
}

void MyQGraphicsTextItem::cmSpotlight()
{
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
    myQTextEdit_->connectMe(this);

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
