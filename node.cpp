#include "node.h"

#include <memory>
#include <sstream>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <cmath>
#include <QGraphicsSceneMouseEvent>

Node::Node(QString text, Node* parent) :
    QGraphicsPathItem(), text_(text), parentNode_(parent), selected_(false)
{
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemClipsToShape, true);
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent * e)
{
    qDebug() << "Node::hoverEnterEvent" << e->type() << zValue() << z_ << text_ << bbox_;
    selected_ = true;
    z_ = zValue();
    setZValue(1);
    update();
    QGraphicsPathItem::hoverEnterEvent(e);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent * e)
{
    qDebug() << "Node::hoverLeaveEvent" << e->type() << zValue() << z_ << text_ << bbox_;
    selected_ = false;
    setZValue(z_);
    update();
//    QGraphicsPathItem::hoverLeaveEvent(e);


}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (parentNode_ == nullptr)
    {
    qDebug() << "top node Node::mouseMoveEvent" << e->type();
    }

//    if (shape().contains(e->pos()))
//    {
//        if (!selected_)
//        {
//            qDebug() << "Mouse is over, but not selected, selecting";

//            selected_ = true;
//            z_ = zValue();
//            setZValue(1);
//            update();
//        }
//    }
//    else if (selected_)
//    {
//        qDebug() << "Mouse is not over, was selected, unselecting";

//        selected_ = false;
//        setZValue(z_);
//        update();
//    }

////    qDebug() << "Node::mouseMoveEvent" << e->type();

    QGraphicsPathItem::mouseMoveEvent(e);

}

bool Node::sceneEvent(QEvent* e)
{
    qDebug() << "Node::sceneEvent" << e->type();
    return QGraphicsPathItem::sceneEvent(e);
}

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent * e)
{
    if (parentNode_ == nullptr)
    {
    qDebug() << "top node Node::hoverMoveEvent" << e->type();
    }
    QGraphicsPathItem::hoverMoveEvent(e);
}

static void optimizeTextBox(QFont& textFont, QRect& textBox, int radius, QString text)
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

}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    int radius = 300;
    painter->save();

//    QBrush background = QBrush(Qt::white);
    QBrush circleBrush = QBrush(QColor(153,204,255));
    QFont textFont;
    textFont.setPixelSize(50);

    QPen textPen(Qt::black);

    QPen selectedPen(Qt::red);
    selectedPen.setWidth(4);

    QPen unselectedPen(Qt::green);
    unselectedPen.setWidth(4);

    painter->setPen( selected_ ? selectedPen : unselectedPen );
    painter->setBrush(circleBrush);

    if (parentNode_ == nullptr)
    {
        qDebug() << "root";

        QPainterPath path;
        path.moveTo(0,0);
        path.addEllipse(QPoint(0,0), radius, radius);

        path_ = path;

        prepareGeometryChange();
        bbox_ = path.boundingRect();
        qDebug() << "bbox_ for top: " << bbox_;

        static bool printme = true;
        if (printme)
        {
            qDebug() << path_ << bbox_;
            printme = false;
        }

        painter->drawPath(path);

        int padding=20;
        QRect textBox(QPoint(-radius+padding, 0), QPoint(radius-padding, 0));

        optimizeTextBox(textFont, textBox, radius-padding, text_);

        QTextOption textOption;
        textOption.setWrapMode(QTextOption::WordWrap);

        painter->setPen(textPen);
        painter->setFont(textFont);
        painter->drawText(textBox, text_, textOption);
    }
    else
    {
        qDebug() << "child: " << QString::number(childIndex);

//        qreal arc = 2 * M_PI / parentNode_->children_.size();

        int radiusInner = radius;
        int radiusOuter = radiusInner + radius;

        QRectF bboxInner(
                    QPointF(-radiusInner, radiusInner),
                    QPointF(radiusInner,-radiusInner)
                    );
        QRectF bboxOuter(
                    QPointF(-radiusOuter, radiusOuter),
                    QPointF(radiusOuter, -radiusOuter)
                    );

        qreal qarc = 360 / parentNode_->children_.size();
        qreal qangleStart = qarc * childIndex;
//        qreal qangleEnd = qarc * (childIndex + 1);

        QPainterPath path;
        path.moveTo(0,0);
        path.arcTo(bboxOuter, qangleStart, qarc);

        QPainterPath subtr;
        subtr.moveTo(0,0);
        subtr.arcTo(bboxInner, qangleStart, qarc);
        path -= subtr;

        path_ = path;
        prepareGeometryChange();

        bbox_ = path.boundingRect();

        static bool printme = true;
        if (printme)
        {
            qDebug() << path_ << bbox_;
            printme = false;
        }
        painter->drawPath(path);

    }

    painter->restore();

}

QRectF Node::boundingRect() const
{
    static int count = 0;
//        qDebug() << "Node::boundintRect()" << bbox_ << count++;
    return bbox_;
}
