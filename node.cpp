#include "node.h"

#include <memory>
#include <sstream>

Node::Node(const std::string& text) : text_(text)
{

}

std::unique_ptr<Node> Node::makeExampleData()
{
    std::unique_ptr<Node> n = std::unique_ptr<Node>(new Node("Top Node"));

    for (std::size_t i = 0 ; i < 3 ; i++)
    {
        std::stringstream ss;
        ss << n->text_ << " / Sub-" << i;
        n->children_.push_back(Node(ss.str()));
    }
    return n;
}
