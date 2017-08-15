
#include "party.h"


namespace objects{


void PartyObservable::add_observer(PartyObserver * observer)
{
    observers.insert(observer);
}


void Party::add_connectivity(common::connectivity_type type, Node * connectingNode)
{
    if (connectivity[static_cast<size_t>(type)].get() != nullptr)
        connectivity[static_cast<size_t>(type)]->add_link(connectingNode);

}


}//namespace objects


