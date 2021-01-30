#ifndef MYQGRAPHICSTEXTITEM_H
#define MYQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include "textedit.h"

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

    }

    void updateText();

    void setEditor(TextEdit* te)
    {
        te_ = te;
    }
signals:
    void selected(QString);

protected:
    TextEdit* te_;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QStyleOptionGraphicsItem myOption(*option);
        myOption.state &= !QStyle::State_Selected;
        QGraphicsTextItem::paint(painter, &myOption, widget);
    }

public:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * e) override;
//    bool sceneEvent(QEvent *) override;
//    bool sceneEvent(QEvent* e)
//    {
//        qDebug() << "MyQGraphicsTextItem::sceneEvent" << e->type();
//        return QGraphicsTextItem::sceneEvent(e);
//    }
    void focusInEvent(QFocusEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYQGRAPHICSTEXTITEM_H
