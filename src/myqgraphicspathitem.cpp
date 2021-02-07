#include "myqgraphicspathitem.h"

#include <memory>
#include <sstream>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QStyleOptionGraphicsItem>
#include <QMenu>
#include "mainwindow.h"
#include "myqgraphicstextitem.h"
#include "node.h"

MyQGraphicsPathItem::MyQGraphicsPathItem(Node* node, QString text) :
    QGraphicsPathItem(), node_(node), text_(text)
{
    if (node_->parentNode_ == nullptr)
    {
        depth_ = 0;
    }
    else
    {
        depth_ = node_->parentNode_->getMyQGraphicsPathItem()->depth_ + 1;
    }

    cacheLineage();

//    qDebug() << depth_ << ": " << text;

    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemClipsToShape, true);

//    initContextMenu();

//    contextMenu_ = new QMenu();
//    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
//    QAction *levelInAction = new QAction("Level In");
//    levelInAction->setShortcuts(QKeySequence::Paste);
//    levelInAction->setStatusTip(tr("Paste the clipboard's contents into the current "
//                                      "selection"));
}

void MyQGraphicsPathItem::cacheLineage()
{
    if (node_->parentNode_)
    {
        MyQGraphicsPathItem* p = node_->parentNode_->getMyQGraphicsPathItem();

        while (p)
        {
            lineage_[p] = p->depth_;
            if (p->node_->parentNode_)
            {
                p = p->node_->parentNode_->getMyQGraphicsPathItem();
            }
            else
            {
                p = nullptr;
            }
        }
    }
}

void MyQGraphicsPathItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* e)
{    
    MyQGraphicsTextItem* ti = dynamic_cast<MyQGraphicsTextItem*>( childItems().at(0));
    ti->contextMenu_->exec(e->screenPos());
//    QAction* focus = new QAction("Focus on element");
//    QAction* levelIn = new QAction("Level in");
//    QAction* levelOut = new QAction("Level out");

//    QMenu menu;
//    QAction* group = menu.addSection("Node");
//    menu.addSeparator();

//    group->addAction("Focus on element");
//    menu.addAction(levelIn);
//    menu.addAction(levelOut);
//    editToolBar->addAction(levelInAction);

//    menu.exec(e->screenPos());

#if 0
    menu.exec(e->screenPos(), focus);
    menu.exec(e->screenPos(), levelIn);
    menu.exec(e->screenPos(), levelOut);

    MyQGraphicsTextItem* ti = dynamic_cast<MyQGraphicsTextItem*>( childItems().at(0));

    qDebug() << "contextMenuEvent";
    qDebug() << MainWindow::globalDegrees_;
    qDebug() << arcStartDegrees_;

    MainWindow::globalDegrees_ = arcStartDegrees_ + arcDegrees_/2.0;

    emit ti->focusThisItem(this);
#endif

//    int incr = 1;
//    if (MainWindow::globalDegrees_ > arcStartDegrees_)
//    {
//        incr = -1;
//    }

//    for (int i = MainWindow::globalDegrees_;
//         abs(arcStartDegrees_ - i) > 0;
//         i += incr )
//    {
//        qDebug() << i;
//        MainWindow::globalDegrees_ = i;
//        update();
//    }
}

#if 0
static qreal optimizeTextBox(QFont& textFont, QRect& textBox, int radius, QString text)
{
    //    qDebug() << "init textBox" << textBox;
    QFontMetrics fm(textFont);
#if 0
    int textWidth = fm.horizontalAdvance(text);
    //    int pixelsHigh = fm.height();

    int lines = std::ceil(double(textWidth) / pixelWidth);

    int height = lines * fm.height() + (lines - 1) * fm.leading();

    int up = height/2;
    int over = pixelWidth/2 - sqrt( pow(pixelWidth/2, 2) - pow(up, 2));
    textBox.setTop(textBox.top()-height/2);
    textBox.setLeft(textBox.left() + over);
    textBox.setBottom(textBox.bottom()+height/2);
    textBox.setRight(textBox.right() - over);

    QSize size = fm.size(Qt::TextWordWrap, text);
    qDebug()
            << "lines" << lines
            << "height" << height
            << "textBox" << textBox;

#endif
    QRect draftBox = textBox;
    draftBox = fm.boundingRect(draftBox, Qt::TextWordWrap, text);
    //    int width0 = draftBox.width();
    //    int height0 = draftBox.height();

    int width1 = 2 * sqrt ( pow(radius, 2) - pow(draftBox.height()/2,2));
    draftBox.setWidth(width1);

    //    qDebug() << "width0" << width0 << "width1" << width1;

    draftBox = fm.boundingRect(draftBox, Qt::TextWordWrap, text);
    int width2 = 2 * sqrt ( pow(radius, 2) - pow(draftBox.height()/2,2) );
    draftBox.setWidth(width2);

    int top = textBox.center().y() - draftBox.height() / 2;
    int bottom = textBox.center().y() + draftBox.height() / 2;
    textBox.setTop(top);
    textBox.setBottom(bottom);

    textBox.setLeft(textBox.center().x() - draftBox.width() / 2);
    textBox.setRight(textBox.center().x() + draftBox.width() / 2);

    //    qDebug() << "draftBox.height()" << draftBox.height();
    //    qDebug() << "width0" << width0 << "width1" << width1 << "width2" << width2;
    //    qDebug() << "draftBox" << draftBox;
    //    qDebug() << "textBox" << textBox;

    return draftBox.width();

}
#endif

void MyQGraphicsPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
//    static int counter = 0;
//    qDebug() << "Node::paint counter: " << ++counter;

    qreal radius = 200;
    painter->save();

    QBrush circleBrush = QBrush(QColor(153,204,255));
    QFont textFont;
    textFont.setPixelSize(50);

    QPen textPen(Qt::black);

    QPen selectedPen(QColor(34,87,171));
    selectedPen.setWidth(6);

    QPen hoveredPen(QColor(140,180,245));
    hoveredPen.setWidth(6);

    QPen unselectedPen(Qt::white);
    unselectedPen.setWidth(6);

    if (hasFocus() || isSelected())
    {
        painter->setPen(selectedPen);
    }
    else if (isUnderMouse())
    {
        painter->setPen(hoveredPen);
    }
    else
    {
        painter->setPen(unselectedPen);
    }

    painter->setBrush(circleBrush);

    int padding=10;

    QTransform tr2;

    if (this == MainWindow::centerMyQGraphicsPathItem_ )
    {
        QPainterPath path;
        path.moveTo(0.0,0.0);
        path.addEllipse(QPoint(0.0,0.0), radius, radius);

        path_ = path;
        bbox_ = path.boundingRect();

//        prepareGeometryChange();

        painter->drawPath(path);
        QGraphicsTextItem* ti = dynamic_cast<QGraphicsTextItem*>( childItems().at(0));

        qreal offset = 0.707106781186547*(radius - padding);

        QPoint origin(-offset, -offset);
        ti->setPos(origin);
        ti->resetTransform();
        if (ti->textWidth() != 2*offset)
        {
            ti->setTextWidth(2*offset);
        }

        arcDegrees_=360;
        arcStartDegrees_=90;
    }
    else if ( lineage_.find(MainWindow::centerMyQGraphicsPathItem_) != lineage_.end() )
    {
        qreal widthFactor = 1;
        int ringLevel = depth_ - MainWindow::centerMyQGraphicsPathItem_->depth_;
        qreal radiusInner = radius * ringLevel;
        qreal radiusOuter = radiusInner + widthFactor*radius;

        QRectF bboxInner(
                    QPointF(-radiusInner, radiusInner),
                    QPointF(radiusInner,-radiusInner)
                    );
        QRectF bboxOuter(
                    QPointF(-radiusOuter, radiusOuter),
                    QPointF(radiusOuter, -radiusOuter)
                    );

        arcDegrees_ = node_->parentNode_->getMyQGraphicsPathItem()->arcDegrees_
                / node_->parentNode_->getMyQGraphicsPathItem()->children_.size();
        qreal qangleStart = node_->parentNode_->getMyQGraphicsPathItem()->arcStartDegrees_ - MainWindow::globalDegrees_;

        QPainterPath path;
        path.arcTo(bboxInner, qangleStart, arcDegrees_);
        path.arcTo(bboxOuter, qangleStart+arcDegrees_, -arcDegrees_);
        path.closeSubpath();

        tr2.rotate(arcDegrees_ * childIndex);
        path_ = tr2.map(path);
//        prepareGeometryChange();

        painter->drawPath(path_);

        static std::map<int,bool> printed;

        bbox_ = path_.boundingRect();

        MyQGraphicsTextItem* ti = dynamic_cast<MyQGraphicsTextItem*>( childItems().at(0));

        qreal arc_r = M_PI * node_->parentNode_->getMyQGraphicsPathItem()->arcDegrees_
                / (180.0 * node_->parentNode_->getMyQGraphicsPathItem()->children_.size());
        qreal angle_r_2 = qangleStart * M_PI / 180.0 + arc_r * (childIndex + 0.5);

        qreal x;
        qreal y;
        QTransform tr;
        qreal rotate;

//        bool updateText = false;
        QString text = /*QString::number(180 * angle_r_2/ M_PI) +*/ this->text_;
        if (text != ti->toPlainText())
        {
//            qDebug() << "update text:" << this->text_ << ti->toPlainText();
            ti->setHtml(text);
//            updateText = true;
        }
        QRectF textBB = ti->boundingRect();

        if ( fabs(angle_r_2) < M_PI / 2.0 || fabs(angle_r_2) > 3 * M_PI / 2.0 )
        {
            // start inside
            qreal theta = atan2(textBB.height()/2.0, radiusInner+padding);
            qreal r = sqrt((radiusInner+padding)*(radiusInner+padding) + textBB.height()*textBB.height()/4.0);
            x = cos(angle_r_2-theta) * r;
            y = sin(angle_r_2-theta) * r;
            rotate = 180 * angle_r_2 / M_PI;
            if (printed.find(childIndex) == printed.end() )
            {
                printed.insert(std::pair<int,bool>(childIndex, true));
            }
        }
        else
        {
            // start outside
            qreal theta = atan2(textBB.height()/2.0, radiusOuter-padding);
            qreal r = sqrt((radiusOuter-padding)*(radiusOuter-padding) + textBB.height()*textBB.height()/4.0);

            x = cos(angle_r_2 + theta) * r;
            y = sin(angle_r_2 + theta) * r;
            rotate = 180 * angle_r_2 / M_PI - 180;
            if (printed.find(childIndex) == printed.end() )
            {
                printed.insert(std::pair<int,bool>(childIndex, true));
            }
        }

        if (ti->textWidth() != widthFactor*radius - 2*padding)
        {
            ti->setTextWidth(widthFactor*radius - 2*padding);
        }

        if (!ti->isVisible())
        {
            ti->setVisible(true);
        }
//        QPoint origin(0,-textBB.height()/2.0`);
//        ti->setPos(origin);
        tr.translate(x,y);
        tr.rotate(rotate);

        ti->setTransform(tr);
        arcStartDegrees_ = node_->parentNode_->getMyQGraphicsPathItem()->arcStartDegrees_
                + childIndex * node_->parentNode_->getMyQGraphicsPathItem()->arcDegrees_
                / node_->parentNode_->getMyQGraphicsPathItem()->children_.size();
    }
    else
    {
        MyQGraphicsTextItem* ti = dynamic_cast<MyQGraphicsTextItem*>( childItems().at(0));
        ti->hide();
    }

    painter->restore();
}

QRectF MyQGraphicsPathItem::boundingRect() const
{
//    static int count = 0;
//        qDebug() << "Node::boundintRect()" << bbox_ << count++;
    return bbox_;
}
