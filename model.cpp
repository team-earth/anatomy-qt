#include "model.h"
#include "node.h"
#include <sstream>
#include <QTextStream>

Model::Model() : centerNode_(nullptr)
{
    loadData(makeExampleData());
    centerNode_ = data_.get();
}

std::unique_ptr<Node> Model::makeExampleData()
{
    std::unique_ptr<Node> n = std::unique_ptr<Node>(new Node("Top Node"));

    for (std::size_t i = 0 ; i < 3 ; i++)
    {
        QTextStream ss;
        ss << n->text_ << " / Sub-" << i;
        n->children_.push_back(Node(ss.readAll()));
    }
    return n;
}

Node* Model::getCenterNode() const
{
    return centerNode_;
}


void Model::loadData(std::unique_ptr<Node> data)
{
    data_ = std::move(data);
}
