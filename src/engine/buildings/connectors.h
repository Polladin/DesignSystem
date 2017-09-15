
#pragma once

#include <list>


namespace objects{

// Forward declaration
class Party;


class Node
{
public:

    Node(Party * party) { parentParty = party; }

    void add_link(Node * node) { edges.push_back(node); }

private:

    // Linked nodes
    std::list<Node *> edges;

    // Party associated with that node
    Party * parentParty;

};


}//namespace objects