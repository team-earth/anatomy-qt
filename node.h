#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>
#include <QString>

class Node
{
public:
    Node(QString text);

//protected:
    QString text_;
    std::vector<Node> children_;


};

#endif // NODE_H
