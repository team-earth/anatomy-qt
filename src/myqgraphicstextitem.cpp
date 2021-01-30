#include "myqgraphicstextitem.h"

void MyQGraphicsTextItem::updateText()
{
    if (te_)
    {
        this->setHtml(te_->toHtml());
    }
}

