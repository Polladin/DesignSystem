
#pragma once

#include "party_observer.h"
#include "engine/common.h"
#include "connectors.h"

#include <list>
#include <memory>


namespace objects{


// Forward declaration
class Party;


/**
 *  PartyObservable :
 *
 */
class PartyObservable
{
public:

    void add_observer(PartyObserver * observer) { observers.insert(observer); }

    void del_observer(PartyObserver * observer) { observers.erase(observer); }

    void notify_all_for_destruction(Party * party)
    {
        for (auto * el : observers)
            el->handle_del_event(party);
    };

private:

    std::set<PartyObserver *> observers;

};


/**
 *  Party :
 *
 */
class Party : public PartyObservable
{

    struct NodeWithPermission
    {
        ActiveObjectPermission aoPermission;
        Node * node;
    };

public:

    //
    void add_connectivity(common::connectivity_type type, Node * connectingNode);

    //
    ~Party() { this->notify_all_for_destruction(this); }

    //


    //std::array<std::unique_ptr<Node>, common::connectivity_type> connectivity;
    std::list<NodeWithPermission> nodesPermissions;
    std::vector<std::unique_ptr<Node>> nodes;

};


}//namespace objects
