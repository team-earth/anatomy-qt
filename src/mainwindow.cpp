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
#include "myqgraphicspathitem.h"
#include "view.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QSettings>
#include <QFontDialog>
#include <QXmlStreamReader>
#include "myqgraphicstextitem.h"
#include "sample_data.h"

int MainWindow::globalDegrees_ = 0;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::CustomMainWindow())
{
    ui->setupUi(this);

    // TODO
    ;

    auto tb = new QToolBar("ToolBar");
    tb->addAction("Action1");
    ui->verticalLayout->setMenuBar(tb);

    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);

    QGraphicsScene* scene = new QGraphicsScene(parent);
    ui->view->setScene(scene);
    ui->textEdit_2->setupToolbar(tb);

//    QString file = "K:/Z/Google Drive/Kevin/anatomy/examples/Politics_where_anger,_threats,_and_polarization_fro.mm";
    //    readFromFile(file);
    readFromString(sample1);

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

void MainWindow::readFromString(QString s)
{
        QXmlStreamReader xmlReader(s);
        xmlReader.readNext();
        while (!xmlReader.isEndDocument())
        {
            if (xmlReader.isStartElement())
            {
                QString name = xmlReader.name().toString();

                if (name.toLower() == "node")
                {
                    rootNode_ = new XmlNode();
                    rootNode_->readNode(xmlReader);
                }
            }
            xmlReader.readNext();
        }
        if (xmlReader.hasError())
        {
            qDebug() << "XML error: " << xmlReader.errorString().data();
        }

//    XmlNode::printNode(rootNode_);
    populateChildren(rootNode_);

}


void MainWindow::readFromFile(QString fn)
{
    QFile file(fn);
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while (!xmlReader.isEndDocument())
        {
            if (xmlReader.isStartElement())
            {
                QString name = xmlReader.name().toString();

                if (name.toLower() == "node")
                {
                    rootNode_ = new XmlNode();
                    rootNode_->readNode(xmlReader);
                }
            }
            xmlReader.readNext();
        }
        if (xmlReader.hasError())
        {
            qDebug() << "XML error: " << xmlReader.errorString().data();
        }
    }

//    XmlNode::printNode(rootNode_);
    populateChildren(rootNode_);
}

MyQGraphicsPathItem* MainWindow::centerNode_ = nullptr;

void MainWindow::populateChildren(XmlNode* xnode)
{
//    QGraphicsItem *item
    QString txt = "<b>MEDIA, NEWS, FACTS.</b> Splintered media landscape reduces common baseline of news facts.";

    txt = xnode->text_;

    MyQGraphicsPathItem* n = new MyQGraphicsPathItem(txt);

    n->setPos(QPointF(0, 0));

    QGraphicsScene* scene = ui->view->scene();

    scene->addItem(n);

    MainWindow::centerNode_ = n;

//    MyQGraphicsItemGroup* group = new MyQGraphicsItemGroup();
//    scene->addItem(group);
//    group->addToGroup(n);
//    n->setZValue(100);

    MyQGraphicsTextItem* ti = new MyQGraphicsTextItem(n);
    ti->setHtml(txt);
//    ti->setTextInteractionFlags(Qt::TextEditorInteraction);
    ti->setEditor(ui->textEdit_2);

    connect(ti, &MyQGraphicsTextItem::selected, ui->textEdit_2, &TextEdit::setText);

    populateChildren(xnode, n);
}

void MainWindow::refresh(const QGraphicsItem* item)
{
    qDebug() << "MainWindow::refresh";
    ui->view->resetCachedContent();
    ui->view->scene()->update(ui->view->sceneRect());
    ui->view->repaint();
//    ui->view->centerOn(item);
    QList<QWidget *> widgets = ui->view->findChildren<QWidget *>();
    foreach (QWidget* w, widgets)
    {
        qDebug() << rect();
         w->repaint(rect());
    }

}

void MainWindow::populateChildren(XmlNode* xnode, MyQGraphicsPathItem* n)
{
    QGraphicsScene* scene = ui->view->scene();

    const int count = xnode->children_.size();
    for (std::size_t i = 0 ; i < count ; i++)
    {
        QString txt = xnode->children_.at(i)->text_; // n->text_ + QString(" / Sub-") + QString::number(i);
        MyQGraphicsPathItem* child = new MyQGraphicsPathItem(txt, n);
        child->childIndex = i;
        n->children_.push_back(child);
        scene->addItem(child);
//        group = new MyQGraphicsItemGroup();
//        ui->view->scene()->addItem(group);
//        group->addToGroup(child);

        MyQGraphicsTextItem* ti = new MyQGraphicsTextItem(child);
        ti->setHtml(txt);
//        ti->setTextInteractionFlags(Qt::TextEditorInteraction);
        ti->setEditor(ui->textEdit_2);
        connect(ti, &MyQGraphicsTextItem::selected, ui->textEdit_2, &TextEdit::setText);
        connect(ti, &MyQGraphicsTextItem::focusThisItem, this, &MainWindow::refresh);

        populateChildren(xnode->children_[i], child);
    }
}

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

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        readFromFile(fileName);
}
