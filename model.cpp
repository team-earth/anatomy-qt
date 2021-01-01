#include "model.h"
#include "node.h"
#include <sstream>

Model::Model()
{
    loadData(makeExampleData());
}

std::unique_ptr<Node> Model::makeExampleData()
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


void Model::loadData(std::unique_ptr<Node> data)
{
    data_ = std::move(data);
}
