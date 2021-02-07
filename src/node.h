#ifndef NODE_H
#define NODE_H

#include <QString>

class MyQGraphicsPathItem;
class MyQTextItem;
class Node
{
public:
    friend class MyQGraphicsPathItem;
    Node(QString text, Node* parentNode = nullptr);

    MyQGraphicsPathItem* getMyQGraphicsPathItem() const;
protected:
    Node* parentNode_;

    MyQGraphicsPathItem* myQGraphicsPathItem_;
    MyQTextItem* myQGraphicsTextItem_;

};

#endif // NODE_H
