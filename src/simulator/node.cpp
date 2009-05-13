#include "node.h"


namespace WSN
{
namespace Simulator
{

Node::Node()
{

    init();
    x=0;
    y=0;

}

Node::Node(int xIn, int yIn)
{
    init();
    x= xIn;
    y=yIn;
    cluster=-1;
}

void Node::init()
{
    energyRemaining=100;///out of a 100 - needs to be changed to a constant MAX_NODE_ENGERGY

}

bool Node::isHead()
{
        return head;
}

void Node::setHead(bool trueForIsTheHead)
{

}

Node::~Node()
{
}

Node Node::getNextHop()
{
    return Node();
}

} /* end of namespace Simulator */

} /* end of WSN namespace */


