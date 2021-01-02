#include "node.h"

#include <memory>
#include <sstream>
#include <QPainter>
#include <cmath>

Node::Node(QString text) : text_(text), parentNode_(nullptr)
{

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

//    painter->fillRect(event->rect(), background);
//    painter->translate(100, 100);

    painter->save();

    QRect v = painter->window();

//    painter->setViewport(v.left() - v.width(), v.right() + v.height()/2, v.width(), v.height() );

//    QRect window = painter->window();

//    painter->translate(v.width()/2, v.height()/2);
//    qreal s = scale/100.0;
//    painter->scale(s,s);

    QBrush background = QBrush(Qt::white);
    QBrush circleBrush = QBrush(QColor(153,204,255));
    QPen circlePen(Qt::white);
    QFont textFont;
    circlePen.setWidth(2);
    QPen textPen(Qt::black);
    textFont.setPixelSize(50);

    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    int radius = 300;
//    int radius = std::min(window.height(), window.width())/2;
    painter->drawEllipse(QPoint(0,0), radius, radius);

    int padding=20;
    QRect textBox(QPoint(-radius+padding, 0), QPoint(radius-padding, 0));
    optimizeTextBox(textFont, textBox, radius-padding, text_);
    QTextOption textOption;
//    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    textOption.setWrapMode(QTextOption::WordWrap);

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(textBox, text_, textOption);

    painter->restore();

}

QRectF Node::boundingRect() const
{

}
