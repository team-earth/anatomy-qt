#ifndef MYQGRAPHICSTEXTITEM_H
#define MYQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include "textedit.h"

class TextEdit;

class MyQGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:

    MyQGraphicsTextItem(QGraphicsItem* parent) : QGraphicsTextItem(parent)
    {
//        connect(QGraphicsTextItem, &QGraphicsTextItem::, this, &TextEdit::setText);
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

public:
//    bool sceneEvent(QEvent* e)
//    {
//        qDebug() << "MyQGraphicsTextItem::sceneEvent" << e->type();
//        return QGraphicsTextItem::sceneEvent(e);
//    }
    void focusInEvent(QFocusEvent *event) override
    {
//        qDebug() << "focusInEvent";
        te_->connectMe(this);

        emit selected(this->toHtml());
        QList<QGraphicsItem*> items = scene()->selectedItems();
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i] != parentItem())
            {
                items[i]->setSelected(false);
            }
        }
        if (parentItem() && !parentItem()->hasFocus())
        {
            parentItem()->setSelected(true);
        }

        QGraphicsTextItem::focusInEvent(event);
    }
};

#endif // MYQGRAPHICSTEXTITEM_H
