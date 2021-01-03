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

#include "mainwindow.h"
#include "ui_custommainwindow.h"
#include "node.h"
#include "view.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

class MyQGraphicsScene : public QGraphicsScene
{
public:
    MyQGraphicsScene(QWidget* parent) : QGraphicsScene(parent) {}

    bool event(QEvent* e)
    {
        //qDebug() << "MyQGraphicsScene::event" << e->type();
        return QGraphicsScene::event(e);
    }
};

//! [0]
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::CustomMainWindow())
{
    ui->setupUi(this);

    MyQGraphicsScene* scene = new MyQGraphicsScene(parent);
    ui->view->setScene(scene);
    populate();

//    ui->view->setModel(&model_);

//    setWindowTitle(tr("Address Book"));

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, ui->view, &View::animate);
//    timer->start(50);

}
//! [0]

void MainWindow::populate()
{
//    QGraphicsItem *item
    Node* n = new Node("MEDIA, NEWS, FACTS. Splintered media landscape reduces common baseline of news facts.");

    n->setPos(QPointF(0, 0));
    ui->view->scene()->addItem(n);
    n->setZValue(100);

    const int count = 3;
    for (std::size_t i = 0 ; i < count ; i++)
    {
        QString t = n->text_ + QString(" / Sub-") + QString::number(i);
        Node* child = new Node(t, n);
        child->childIndex = i;
        n->children_.push_back(child);
        ui->view->scene()->addItem(child);
    }
}

//! [2]
void MainWindow::openFile()
{
//    QString fileName = QFileDialog::getOpenFileName(this);
//    if (!fileName.isEmpty())
//        addressWidget->readFromFile(fileName);
}
//! [2]

//! [3]
void MainWindow::saveFile()
{
//    QString fileName = QFileDialog::getSaveFileName(this);
//    if (!fileName.isEmpty())
//        addressWidget->writeToFile(fileName);
}
//! [3]

//! [4]
void MainWindow::updateActions(const QItemSelection &selection)
{
//    QModelIndexList indexes = selection.indexes();

//    if (!indexes.isEmpty()) {
//        removeAct->setEnabled(true);
//        editAct->setEnabled(true);
//    } else {
//        removeAct->setEnabled(false);
//        editAct->setEnabled(false);
//    }
}
//! [4]

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
