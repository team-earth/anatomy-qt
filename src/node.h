#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QVector>
#include <unordered_map>

class MyQGraphicsPathItem;
class MyQGraphicsTextItem;
class Node
{
public:
    friend class MyQGraphicsPathItem;
    friend class MyQGraphicsTextItem;
    friend class MainWindow;
    Node(QString text, Node* parentNode = nullptr);

    MyQGraphicsPathItem* getMyQGraphicsPathItem() const;
    MyQGraphicsTextItem* getMyQGraphicsTextItem() const;
protected:
    void cacheLineage();

    Node* parentNode_;

    MyQGraphicsPathItem* myQGraphicsPathItem_;
    MyQGraphicsTextItem* myQGraphicsTextItem_;

    QVector<Node*> children_;
    int childIndex;
    int depth_;

    std::unordered_map<Node*, int> lineage_;

};

#endif // NODE_H
