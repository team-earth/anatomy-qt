#include "node.h"

#include <memory>
#include <sstream>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

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
//    qDebug() << "Node::hoverEnterEvent" << e->type() << zValue() << z_ << text_ << bbox_;
    selected_ = true;
    z_ = zValue();
    setZValue(1);
    update();
    QGraphicsPathItem::hoverEnterEvent(e);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent * e)
{
//    qDebug() << "Node::hoverLeaveEvent" << e->type() << zValue() << z_ << text_ << bbox_;
    selected_ = false;
    setZValue(z_);
    update();
    QGraphicsPathItem::hoverLeaveEvent(e);


}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
//    if (parentNode_ == nullptr)
//    {
//    qDebug() << "top node Node::mouseMoveEvent" << e->type();
//    }

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
//    qDebug() << "Node::sceneEvent" << e->type();
    return QGraphicsPathItem::sceneEvent(e);
}

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent * e)
{
//    if (parentNode_ == nullptr)
//    {
//    qDebug() << "top node Node::hoverMoveEvent" << e->type();
//    }
    QGraphicsPathItem::hoverMoveEvent(e);
}

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

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    qreal radius = 300;
    painter->save();

//    QBrush background = QBrush(Qt::white);
    QBrush circleBrush = QBrush(QColor(153,204,255));
    QFont textFont;
    textFont.setPixelSize(50);

    QPen textPen(Qt::black);

    QPen selectedPen(QColor(140,180,245));
    selectedPen.setWidth(6);

    QPen unselectedPen(Qt::white);
    unselectedPen.setWidth(6);

    painter->setPen( selected_ ? selectedPen : unselectedPen );
    painter->setBrush(circleBrush);

    int padding=20;

    if (parentNode_ == nullptr)
    {
//        qDebug() << "root";

        QPainterPath path;
        path.moveTo(0.0,0.0);
        path.addEllipse(QPoint(0.0,0.0), radius, radius);

        path_ = path;

        prepareGeometryChange();
        bbox_ = path.boundingRect();
//        qDebug() << "bbox_ for top: " << bbox_;

//        static bool printme = true;
//        if (printme)
//        {
//            qDebug() << path_ << bbox_;
//            printme = false;
//        }

        painter->drawPath(path);

        QGraphicsTextItem* ti = dynamic_cast<QGraphicsTextItem*>( childItems().at(0));

        qreal offset = 0.707106781186547*(radius - padding);

//        QRect textBox(QPoint(-radius+padding, 0), QPoint(radius-padding, 0));

//        QString text = ti->toHtml();
//        qreal width = optimizeTextBox(textFont, textBox, radius-padding, text);

        QPoint origin(-offset, -offset);
        ti->setPos(origin);
        ti->setTextWidth(2*offset);

        //        ti->setHtml("Ok"+text_);
//        QTextOption textOption;
//        textOption.setWrapMode(QTextOption::WordWrap);

//        painter->setPen(textPen);
//        painter->setFont(textFont);
//        painter->drawText(textBox, text_, textOption);


    }
    else
    {
//        qDebug() << "child: " << QString::number(childIndex);

//        qreal arc = 2 * M_PI / parentNode_->children_.size();

        qreal radiusInner = radius;
        qreal radiusOuter = radiusInner + 2.0*radius;

        QRectF bboxInner(
                    QPointF(-radiusInner, radiusInner),
                    QPointF(radiusInner,-radiusInner)
                    );
        QRectF bboxOuter(
                    QPointF(-radiusOuter, radiusOuter),
                    QPointF(radiusOuter, -radiusOuter)
                    );

        qreal qarc = 360.0 / parentNode_->children_.size();
        qreal qangleStart = qarc * childIndex;
//        qreal qangleEnd = qarc * (childIndex + 1);


        QPainterPath path;
        path.moveTo(0.0,0.0);
        path.arcTo(bboxOuter, qangleStart, qarc);
        path.setFillRule(Qt::WindingFill);


        QPainterPath subtr;
//        subtr.moveTo(0.0,0.0);
        subtr.arcTo(bboxInner, qangleStart, qarc);
        subtr.setFillRule(Qt::WindingFill);

        path -= subtr;

        path_ = path; //.subtracted(subtr);
        path_.setFillRule(Qt::WindingFill);

        bbox_ = path_.boundingRect();

//        QRect textBox(QPoint(-radius+padding, 0), QPoint(radius-padding, 0));
//        optimizeTextBox(textFont, textBox, radius-padding, text_);

        prepareGeometryChange();
        painter->drawPath(path);

#if 1
        QGraphicsTextItem* ti = dynamic_cast<QGraphicsTextItem*>( childItems().at(0));

        qreal arc_r = 2 * M_PI / parentNode_->children_.size();
        qreal angle_r_1 = arc_r * (childIndex - 0.5);
        qreal angle_r_2 = arc_r * (childIndex + 0.5);

        qreal x;
        qreal y;
        QTransform tr;
        qreal rotate;
        if (angle_r_2 < M_PI / 2.0 || angle_r_2 > 3 * M_PI / 2.0 )
        {
            // lower hemishphere
            x = cos(angle_r_2) * radiusInner;
            y = sin(angle_r_2) * radiusInner;
            rotate = 180 * angle_r_2 / M_PI;
            ti->setHtml(QString::number(rotate) + " f " + QString::number(childIndex));
        }
        else
        {
            // upper hemisphere
            x = cos(angle_r_2) * radiusOuter;
            y = sin(angle_r_2) * radiusOuter;
            rotate = 180 * angle_r_2 / M_PI - 180;
            ti->setHtml(QString::number(rotate) + " r " + QString::number(childIndex));
        }

        tr.rotate(rotate);

        QPoint origin(x, y);
        ti->setPos(origin);
        ti->setTextWidth(2*radius /* - 2*padding*/);

        ti->setTransform(tr);
#endif
//        QTextDocument td;
//        td.setHtml("<b>This</b> is an example of <i>text</i>.");
//        QAbstractTextDocumentLayout::PaintContext ctx;
//        painter->translate(QPointF(300,0));
//        td.documentLayout()->draw(painter, ctx);
    }

    painter->restore();

}

QRectF Node::boundingRect() const
{
    static int count = 0;
//        qDebug() << "Node::boundintRect()" << bbox_ << count++;
    return bbox_;
}
