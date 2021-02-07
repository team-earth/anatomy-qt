/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#if 0
#include "paintHelper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QDebug>
#include <QTextOption>
#include <QFontMetrics>
#include <cmath>

//! [0]
PaintHelper::PaintHelper()
{
//    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
//    gradient.setColorAt(0.0, Qt::green);
//    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(Qt::white);
    circleBrush = QBrush(QColor(153,204,255));
    circlePen = QPen(Qt::white);
    circlePen.setWidth(2);
    textPen = QPen(Qt::black);
    textFont.setPixelSize(50);
}
//! [0]

void PaintHelper::paint(QPainter *painter, QPaintEvent *event, MyQGraphicsPathItem* node, int scale)
{
    painter->fillRect(event->rect(), background);

//    painter->fillRect(event->rect(), background);
//    painter->translate(100, 100);

    painter->save();

    QRect v = painter->window();

//    painter->setViewport(v.left() - v.width(), v.right() + v.height()/2, v.width(), v.height() );

//    QRect window = painter->window();

    painter->translate(v.width()/2, v.height()/2);
    qreal s = scale/100.0;
    painter->scale(s,s);

    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    int radius = 300;
//    int radius = std::min(window.height(), window.width())/2;
    painter->drawEllipse(QPoint(0,0), radius, radius);

    int padding=20;
    QRect textBox(QPoint(-radius+padding, 0), QPoint(radius-padding, 0));
    optimizeTextBox(textFont, textBox, radius-padding, node->text_);
    QTextOption textOption;
//    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    textOption.setWrapMode(QTextOption::WordWrap);

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(textBox, node->text_, textOption);

    painter->restore();

}

void PaintHelper::optimizeTextBox(QFont& textFont, QRect& textBox, int radius, QString text)
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


//! [1]
void PaintHelper::paintOld(QPainter *painter, QPaintEvent *event, MyQGraphicsPathItem& node)
{
    int elapsed=0;
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);
//! [1]

//! [2]
    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
    painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 120.0 * factor;
        qreal circleRadius = 1 + factor * 20;
        painter->drawEllipse(QRectF(radius, -circleRadius,
                                    circleRadius * 2, circleRadius * 2));
    }
    painter->restore();
//! [2]

//! [3]
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("KK"));
    qDebug() << "PaintHelper::paintOld()";

}
//! [3]
#endif
