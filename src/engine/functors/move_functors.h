


namespace map{

// Forward declaration
class Map;

}//namespace map


namespace vehicle{

// Forward declaration
class VehicleUnit;

}//namespace vehicle


namespace functors{


class MoveSimpleFunctor
{
public:

void operator() (vehicle::VehicleUnit * activeObject, map::Map * mapObject);

};


}//namespace functors