
#pragma once


namespace objects{


// Forward declaration
class Party;


class PartyObserver
{
public:

    void handle_del_event(Party * party) = 0;

};


}//namespace objects