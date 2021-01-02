#include "node.h"

#include <memory>
#include <sstream>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <cmath>
#include <QGraphicsSceneMouseEvent>

Node::Node(QString text, Node* parent) :
    QGraphicsPathItem(parent), text_(text), parentNode_(parent), selected_(false)
{
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent * e)
{
    qDebug() << "Node::hoverEnterEvent" << e->type() << text_;
    selected_ = true;
    setZValue(1);
    update();
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent * e)
{
    qDebug() << "Node::hoverMouseEvent" << e->type() << text_;
    selected_ = false;
    setZValue(0);
    update();

}

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent * e)
{
//    qDebug() << "Node::hoverMoveEvent" << e->type();

}

bool Node::sceneEvent(QEvent* e)
{
//    qDebug() << "Node::sceneEvent" << e->type();
    return QGraphicsPathItem::sceneEvent(e);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    qDebug() << "Node::mouseMoveEvent" << e->type();
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
//        qDebug() << "root" << painter->pen();

        QPainterPath path;
        path.moveTo(0,0);
        path.addEllipse(QPoint(0,0), radius, radius);

        path_ = path;

        prepareGeometryChange();
        bbox_ = path.boundingRect();

//        qDebug() << bbox_ << path_;

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
//        qDebug() << QString::number(childIndex) << painter->pen();

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

//        qDebug() << bboxInner << qarc << qangleStart << qangleEnd;

        painter->drawPath(path);

        //        painter->setPen(QPen(Qt::green));

        //        painter->drawArc(
        //                    QRectF(
        //                        QPointF(-300,-300),
        //                        QPointF(300,300)
        //                        ),
        //                    -1440,
        //                    2880);

        //        painter->setPen(QPen(Qt::black));

        //        painter->setBrush(QBrush());
        //        painter->drawRect(
        //                    QRectF(
        //                        QPointF(-300,-300),
        //                        QPointF(300,300)
        //                        )
        //                    );

    }

    painter->restore();

}

QRectF Node::boundingRect() const
{
    static int count = 0;
//        qDebug() << "Node::boundintRect()" << bbox_ << count++;
    return bbox_;
}
