#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

class Node
{
public:
    Node(const std::string& text);

//protected:
    std::string text_;
    std::vector<Node> children_;


};

#endif // NODE_H
