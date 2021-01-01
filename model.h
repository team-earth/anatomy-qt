#ifndef MODEL_H
#define MODEL_H

#include "node.h"

class Model
{
public:
    Model();
    void loadData(std::unique_ptr<Node>);

    Node* getCenterNode() const;

protected:
    std::unique_ptr<Node> data_;
    static std::unique_ptr<Node> makeExampleData();
    Node* centerNode_;

};

#endif // MODEL_H
