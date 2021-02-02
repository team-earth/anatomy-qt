#ifndef MYQGRAPHICSTEXTITEM_H
#define MYQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include <QStyle>
#include <QMenu>
#include <QStyleOptionGraphicsItem>
#include "textedit.h"
#include "mainwindow.h"

class TextEdit;

class MyQGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:

    MyQGraphicsTextItem(QGraphicsItem* parent) : QGraphicsTextItem(parent)
    {
//        connect(QGraphicsTextItem, &QGraphicsTextItem::, this, &TextEdit::setText);
//        setFlag(QGraphicsItem::ItemIsFocusable, false);
//        setFlag(QGraphicsItem::ItemIsSelectable, false);
//        setCursor(Qt::BlankCursor);
        setTextInteractionFlags(Qt::TextEditorInteraction);

        QAction *focusAction = new QAction("Focus");
        QAction *levelInAction = new QAction("Level In");
        QAction *levelUpAction = new QAction("Level Up");

        contextMenu_ = new QMenu();
        contextMenu_->addAction(focusAction);
        contextMenu_->addAction(levelInAction);
        contextMenu_->addAction(levelUpAction);

        connect(focusAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmFocus);
        connect(levelInAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmLevelIn);
        connect(levelUpAction, &QAction::triggered, this, &MyQGraphicsTextItem::cmLevelUp);

    }

    void cmLevelIn();
    void cmLevelUp();

    void cmFocus()
    {
        qDebug() << "cmFocus";
        Node* p = dynamic_cast<Node*>(parentItem());

        MainWindow::globalDegrees_ = p->arcStartDegrees_ + p->arcDegrees_/2.0;

        emit focusThisItem(this);
    }

    void updateText();

    void setEditor(TextEdit* te)
    {
        te_ = te;
    }

    QMenu* contextMenu_;
signals:
    void selected(QString);
    void focusThisItem(const QGraphicsItem*);


protected:
    TextEdit* te_;

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
//    {
//        QStyleOptionGraphicsItem myOption(*option);
//        myOption.state &= !QStyle::State_Selected;
//        QGraphicsTextItem::paint(painter, &myOption, widget);
//    }

public:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * e) override;
//    bool sceneEvent(QEvent *) override;
//    bool sceneEvent(QEvent* e)
//    {
//        qDebug() << "MyQGraphicsTextItem::sceneEvent" << e->type();
//        return QGraphicsTextItem::sceneEvent(e);
//    }
    void focusInEvent(QFocusEvent *event) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYQGRAPHICSTEXTITEM_H
