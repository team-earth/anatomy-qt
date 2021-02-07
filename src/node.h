#ifndef NODE_H
#define NODE_H

#include <QString>

class MyQGraphicsPathItem;
class MyQGraphicsTextItem;
class Node
{
public:
    friend class MyQGraphicsPathItem;
    Node(QString text, Node* parentNode = nullptr);

    MyQGraphicsPathItem* getMyQGraphicsPathItem() const;
    MyQGraphicsTextItem* getMyQGraphicsTextItem() const;
protected:
    Node* parentNode_;

    MyQGraphicsPathItem* myQGraphicsPathItem_;
    MyQGraphicsTextItem* myQGraphicsTextItem_;
};

#endif // NODE_H
