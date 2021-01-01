#ifndef MODEL_H
#define MODEL_H

#include "node.h"

class Model
{
public:
    Model();
    void loadData(std::unique_ptr<Node>);

protected:
    std::unique_ptr<Node> data_;
    static std::unique_ptr<Node> makeExampleData();

};

#endif // MODEL_H
