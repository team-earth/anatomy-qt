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
#include <QSettings>
#include <QFontDialog>
#include "myqgraphicstextitem.h"

//class MyQGraphicsScene : public QGraphicsScene
//{
//public:
//    MyQGraphicsScene(QWidget* parent) : QGraphicsScene(parent) {}

//    bool event(QEvent* e)
//    {
//        //qDebug() << "MyQGraphicsScene::event" << e->type();
//        return QGraphicsScene::event(e);
//    }
//};

//class MyQGraphicsItemGroup : public QGraphicsItemGroup
//{
//public:
//    MyQGraphicsItemGroup(QGraphicsItem *parent = nullptr) :
//        QGraphicsItemGroup(parent)
//    {
//        setAcceptHoverEvents(true);
//        setAcceptTouchEvents(true);
//        setFlag(QGraphicsItem::ItemIsMovable, true);
//        setFlag(QGraphicsItem::ItemIsSelectable, true);
//        setFlag(QGraphicsItem::ItemIsFocusable, true);
//        setFlag(QGraphicsItem::ItemClipsToShape, true);
//    }
//};

//static void test(MyQGraphicsScene* scene)
//{

//    MyQGraphicsItemGroup* group = new MyQGraphicsItemGroup();
//    scene->addItem(group);

//    QGraphicsTextItem* ti = new QGraphicsTextItem();
//    ti->setHtml("<b>This</b> is a text");
//    ti->setTextInteractionFlags(Qt::TextEditorInteraction);
//    //ui->view->scene()->addItem(ti);
////    scene->addItem(ti);
//    group->addToGroup(ti);

//}

//! [0]
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::CustomMainWindow())
{



    ui->setupUi(this);


    auto tb = new QToolBar("ToolBar");
    tb->addAction("Action1");
    ui->verticalLayout->setMenuBar(tb);

    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);

    QGraphicsScene* scene = new QGraphicsScene(parent);
    ui->view->setScene(scene);

    ui->textEdit_2->setupToolbar(tb);
    populate();

    readSettings();

//    QList<QObject*> list = this->findChildren<QObject*>();
//    foreach (auto obj, list)
//    {
//        qDebug() <<obj->objectName(); // << obj;
//    }

//    ui->view->setModel(&model_);

//    setWindowTitle(tr("Address Book"));

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, ui->view, &View::animate);
//    timer->start(50);

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (true /*userReallyWantsToQuit()*/) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }

}

void MainWindow::writeSettings()
{
//    qDebug() << "MainWindow::writeSettings";
    QSettings settings("team.earth", "anatomy");
    settings.setValue("mainwindow/geometry", saveGeometry());
    settings.setValue("mainwindow/windowState", saveState());
}

void MainWindow::readSettings()
{
    QSettings settings("team.earth", "anatomy");
//    auto keys = settings.allKeys();
//    for (size_t i = 0; i < keys.size(); i++)
//    {
//        qDebug() << keys[i] << settings.value(keys[i]);
//    }
    restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    restoreState(settings.value("mainwindow/windowState").toByteArray());
}

void MainWindow::populate()
{
//    QGraphicsItem *item
    QString txt = "<b>MEDIA, NEWS, FACTS.</b> Splintered media landscape reduces common baseline of news facts.";

    Node* n = new Node(txt);

    n->setPos(QPointF(0, 0));

    QGraphicsScene* scene = ui->view->scene();

    scene->addItem(n);

//    MyQGraphicsItemGroup* group = new MyQGraphicsItemGroup();
//    scene->addItem(group);
//    group->addToGroup(n);
//    n->setZValue(100);

    MyQGraphicsTextItem* ti = new MyQGraphicsTextItem(n);
    ti->setHtml(txt);
    ti->setTextInteractionFlags(Qt::TextEditorInteraction);
//    n->setFocusProxy(ti);

//    scene->addItem(ti);
//    group->addToGroup(ti);

    const int count = 6;
    for (std::size_t i = 0 ; i < count ; i++)
    {
        QString txt = n->text_ + QString(" / Sub-") + QString::number(i);
        Node* child = new Node(txt, n);
        child->childIndex = i;
        n->children_.push_back(child);
        scene->addItem(child);
//        group = new MyQGraphicsItemGroup();
//        ui->view->scene()->addItem(group);
//        group->addToGroup(child);

        MyQGraphicsTextItem* ti = new MyQGraphicsTextItem(child);
        ti->setHtml(txt);
        ti->setTextInteractionFlags(Qt::TextEditorInteraction);
        ti->setEditor(ui->textEdit_2);
        connect(ti, &MyQGraphicsTextItem::selected, ui->textEdit_2, &TextEdit::setText);

//        child->setFocusProxy(ti);

//        scene->addItem(ti);
//        group->addToGroup(ti);

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

void MainWindow::on_actionFont_triggered()
{
    bool ok;

    QWidget* widget = QApplication::focusWidget();
    qDebug() << widget;

    QList<QGraphicsItem *> items = ui->view->scene()->selectedItems();

    qDebug() << items;

    if (items.size() > 0)
    {
        QFont initFont ; //= items[0]->font();
//        qDebug() << initFont;

        QFont font = QFontDialog::getFont(&ok, initFont, this);
        if (ok)
        {
            widget->setFont(font);
        }
    }
}
